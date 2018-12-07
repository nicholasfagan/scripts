var net = require('net');
var readline = require('readline');
//var os = require('os');
//var ifaces = os.networkInterfaces();
//var ip = ifaces[Object.keys(ifaces)[0]].address;


exports.run = ( host, port) => {
	var PORT = 8080;
	var connections = [];
	var registered = [];
	var HOST = host;
	
	const send = (s, m) => {
		s.write(JSON.stringify(m));
	};
	const broadcast = (msg) => {
		registered.forEach((s)=>send(s, msg));
		console.log(msg);
	};
	const validatePasswd = (p) => {return p=='password';};
	const register = (sock, m)=> {
		if(m.type === 'register') {
			var found = false;
			for(var i = 0; i < connections.length; i++) {
				if(connections[i].name == m.name) {
					found=true;
					break;
				}
			}
			if(found) {
				send(sock,{type:'err',err:'ERR_NAME_TAKEN'});
				m.name = Math.random().toString(36)
			}
			var c = new Object();
			c.name = m.name || '';
			c.socket = sock;
			c.since = new Date();
			connections.push(c);
			registered.push(sock);
			broadcast({
				type:'announcment',
				message:'User \'' +c.name+ '\' Connected'
			});
		}else {
			send(sock, {type:'err',err:'ERR_NOT_REGISTERED'});
		}
	}
	const clientparse = (s, m) => {
		var c = null;
		for(var i = 0; i < connections.length; i++) 
			if(connections[i].socket == s) { 
				c = connections[i];
				break;
			}
		if(c == null) {
			console.log('Internal Error.');
			send(s,{type:'err',err:'ERR_INTERNAL'});
			s.destroy();
			return;
		}
		switch (m.type) {
			case 'err':
				console.log({socket:s,msg:m});
				s.destroy();
				break;
			case 'gchat':
				//global chat
				if((m.message || '') == '') {
					send(s,{type:'err',err:'ERR_PROTOCOL'});
					s.destroy();	
				}else broadcast({type:'gchat',name:c.name,message:m.message});
				break;
			case 'pchat':
				//attributes to and message
				if((m.to || '') == '' && (m.message || '') == '') {
					send(s,{type:'err',err:'ERR_PROTOCOL'});
					s.destroy();
				}else {
					var index = -1;
					for(var i = 0; i < connections.length; i++) {
						if(connections[i].name == m.to) {
							index = i;
							break;
						}
					}
					if(index > -1) {
						send(connections[i].socket, {
							type:'pchat',
							name:c.name,
							message:m.message
						});
					}else {
						send(s,{type:'err',err:'ERR_NOT_USER'});
					}
				}
				break;
			case 'cmd':
				switch(m.cmd) {
					case 'op':
						if(validatePasswd(m.passwd)){
							c.isop = true;
							send(s,{type:'status',success:true});
						}else 
							send(s,{type:'status',success:false});
						break;
					case 'kick':
						if(c.isop) {
							var index = -1;
							for(var i = 0; i < connections.length; i++) {
								if(connections[i].name == m.name) {
									index = i;
									break;
								}
							}
							if(index > -1) {
								connections[i].socket.on('close',() => {
									broadcast({
										type:'announcment',
										message:'User \'' + m.name + '\' was kicked by \'' + c.name + '\''
									});
								});
								connections[i].socket.destroy();
							}else {
								send(s,{type:'err',err:'ERR_NOT_USER'});
							}
						}else 
							send(s,{type:'status',success:false});
						break;
					case 'name':
						var found = false;
						for(var i = 0; i < connections.length; i++) {
							if(connections[i].name == m.name) {
								found=true;
								break;
							}
						}
						if(found) {
							send(s,{type:'err',err:'ERR_NAME_TAKEN'});
							break;
						}
						


						
						var oldn = c.name;
						c.name = m.name || '';
						
						broadcast({
							type:'announcment',
							message:'\'' + oldn + '\' is now \'' + c.name + '\''
						});
						break;
					default:
						send(s,{type:'err',err:'ERR_PROTOCOL'});
						s.destroy();
						break;
				}
				break;
			default: 
				send(s,{type:'err',err:'ERR_PROTOCOL'});
				s.destroy();
				break;

		}
	};
	const handle = (sock) => {
		sock.on('close', () =>{
			var index = -1;
			var n = null;
			for(var i = 0; i < connections.length; i++) 
				if(connections[i].socket === sock) {
					index = i;
					break;
				}
			if (index > -1) {
				n = connections[index].name;
				connections.splice(index, 1);
			}
			index = registered.indexOf(sock);
			if(index > -1) registered.splice(index, 1);
			if(n != null) broadcast({
				type: 'announcment',
				message:"User '" + n + "' Disconnected."
			});
		});
		sock.on('data', (data) => {
			try {
				var msg = JSON.parse(data);
				if(registered.indexOf(sock) == -1) register(sock, msg);
				else clientparse(sock, msg);
			} catch(e) {
				send(sock,{type:'err',err:'ERR_PROTOCOL'});
				sock.destroy();

			}
		});
	};
	const nio = net.createServer(handle);
	const help = () => {
		console.log("\n" + 
			"help  : help | h | ?\n" +
			"        prints this help message.\n" + 
			"exit  : exit | quit | q | close\n" + 
			"        closes the server and exits.\n" + 
			"count : count | c\n" + 
			"        prints number of active connections.\n" + 
			"print : print | p | info\n" + 
			"        prints address of all connections\n");
	}
	const count = () => {
		getCount((n) => {
			console.log("There are %d connections.",n);
		});
	};

	const print = () => {
		connections.forEach((c) => {
			console.log(c.name);
		});
	};
	const getCount = (callback) => {
		nio.getConnections((err, count) => {
			if(err) callback(0);
			callback(count);
		});
	};
	const quit = () => {
		nio.close((err) => {
			if(err) {
				console.log("Server was not running.");
			}else {
				console.log("Server Closed.");
			}
			cio.close();
			process.exit(0);
		});
		for(var i = 0; i < registered.length; i++) registered[i].destroy();
	};
	const conparse = (str) => {
		switch(str.trim().split(' ')[0]) {
			default:
			case 'help':
			case 'h':
			case '?':
				help();
				break
			case 'exit':
			case 'quit':
			case 'q':
			case 'close':
				quit();
				break;
			case 'count':
			case 'c':
				count();
				break;
			case 'info':
			case 'p':
			case 'print':
				print();
				break;
			case 'b':
				break;
			case '':
				break;
		}
	};
	nio.on('error', (e) => {
		if(e.code === 'EADDRINUSE') {
			console.log('Port in use. Retrying . . .');
			setTimeout(() => {
				nio.close();
				nio.listen(PORT,HOST);
			}, 1000);
		}
	});
	const cio = readline.createInterface({
		input: process.stdin,
		output: process.stdout
	});
	PORT = port;
	cio.on('line',conparse);
	cio.on('SIGINT', quit);
	console.log("Running server on port " + port);
	nio.listen(port, HOST);
};
