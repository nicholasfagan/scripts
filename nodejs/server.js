var http = require('http');
var util = require('util');
var url = require('url');
var fs = require('fs');
var path=require('path');
var port = process.argv[2] || 8080;

function cleanPath(s) {
	return s.replace("//","/");
}
function safeGetFile(filename, success, failure) {
	fs.readFile(filename, function(err, data){
		if(err) failure();
		else success(data);
	});
}
function serve(response, resCode, data) {
	response.writeHead(resCode, {'Content-Type': 'text/html'});
	response.write(data, "binary");
	response.end();
	console.log("Response");
	console.log("  HTTP : '" + resCode + "'");	
	console.log();
}

http.createServer(function (req, res) {
	var uri = url.parse(req.url).pathname;
	var filename = path.join(process.cwd(), uri);
	console.log("Request");
	console.log("  for  : '" + filename + "'");
	console.log("  from : '" + req.connection.remoteAddress + "'");
	safeGetFile(filename, 
	function(data){
		//exact pathname
		serve(res, 200, data);
	}, function(){
		//exact failed, try adding /index.html
		safeGetFile(cleanPath(filename + '/index.html'), function(data){
			serve(res, 200, data);
		},function(){
			//that failed. serve 404
			safeGetFile('./404.html', 
			function(data){
				//404 page exists
				serve(res, 404, data);
			},function(){
				//generic 404 
				serve(res, 404, "404 Not Found");
			});
		});
	});
}).listen(port, 10);

//info
console.log("Server running on");
console.log("  Address : localhost");
console.log("  Port    : " + port);
console.log("CTRL-C to stop.\n");

