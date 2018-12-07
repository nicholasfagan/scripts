var net = require('net');
var chalk = require('chalk');
var readline = require('readline');
exports.run = (host, port, name) => {
	var alias, HOST, PORT;
	var global = true;
	var cio = readline.createInterface({
		input: process.stdin,
		output: process.stdout
	});
	var nio = new net.Socket();
	cio.on('SIGINT',()=>nio.destroy());
	nio.on('error',(e)=> {
		if(e.code==='ECONNREFUSED'){ 
			console.log('Connection Refused.');
			console.log('Make sure the server is running,\nand you have the correct address and port.');
			process.exit(0);

		}
	});
	alias = name;
	HOST = host;
	PORT = port;
	const cutFirst = (str,delim) => {
		var arr = str.split(delim);
		var fst = arr.splice(0,1);
		return [fst.join(""),arr.join(delim)];
	}
	const send = (m) => nio.write(JSON.stringify(m));
	const print = (m) => {
		switch(m.type) {
			case 'gchat':
				if(global) console.log("[G]["+m.name+"]: "+m.message);
				break;
			case 'pchat':
				console.log(chalk.bold("[P]["+m.name+"]: ")+m.message);
				break;
			case 'err':
				console.log(chalk.red("[Error]: ") + m.err);
				break;
			case 'announcment':
				console.log(chalk.cyan(m.message));
				break;
			case 'status':
				if(m.success) console.log(chalk.green("Successful"));
				else console.log(chalk.yellow("Unsuccessful"));
				break;
			default:
				console.log(m);
				break;
		}
	};
	var handle = (err) => {
		send({type:'register',name:name});
		nio.on('close',()=>{
			console.log(chalk.cyan('Connection Closed'));
			process.exit(0);
		});
		nio.on('data',(data) => {
			var msg = JSON.parse(data);
			print(msg);
		});
	};
	nio.connect(port, host, handle);
	const help = () => {
		console.log();
		console.log("HELP PAGE");
		console.log("Commands start with '/'");
		console.log("help page          :    /? | /h");
		console.log("private chat       :    /p <name> <message>");
		console.log("global chat        :    just type, no command");
		console.log("exit | quit        :    /q");
		console.log("toggle global chat :    /g on|off");
		console.log("change name        :    /name <name>");
		console.log();

	}
	cio.on('line', (str) => {
		
		if(str.startsWith("/")) {
			var p1 = cutFirst(str," ");
			if(p1[0] == "/pchat" || p1[0] == "/p" ) {//private message
				send({
					type:'pchat',
					to:cutFirst(p1[1]," ")[0],
					message:cutFirst(p1[1]," ")[1]
				});
			} else if(p1[0]=="/name") {
				if(p1[1].indexOf(' ')!==-1) {
					print({type:'err',err:'ERR_INVALID'});
				}else
					send({
						type:'cmd',
						cmd:'name',
						name:p1[1]
					});
			} else if(p1[0]=="/op") {
				send({
					type:'cmd',
					cmd:'op',
					passwd:p1[1]
				});
			} else if(p1[0]=="/kick") {
				send({
					type:'cmd',
					cmd:'kick',
					name:p1[1]
				});
			}else if(str=="/h"||str=="/?") {
				help();
			} else if(p1[0] == "/q") {
				nio.destroy();
			}else if (str == '/g off') {
				global = false;
				print({type:'announcment',message:'Global messages disabled'});
			} else if(str=='/g on') {
				global = true;
				print({type:'announcment',message:'Global messages enabled'});
			} else {
				print({type:'err',err:'ERR_CMD'});
				help();
			}
		}
		else if(str != '') send({type:'gchat',message:str});
	});
};
