
var fs = require('fs');
const readline = require('readline');
const rl = readline.createInterface({
	input: process.stdin,
	output: process.stdout
});
var db;
console.log("Loading . . .");
fs.readFile('db.js',(err,fdata)=>{
	if(err || fdata == '') {
		console.log("Creating new DB . . . ");
		db = {q:'Is it an animal',y:{a:'dog'},n:{a:'toaster'}};
	} else {
		console.log("Parsing . . .");
		db = JSON.parse(fdata);
	}
	console.log("Ready.\n");
	ask(db);
});
var done = () => {
	rl.question('Want to play again? (y/n): ', (response)=>{
		switch(response) {
			case 'y':
				ask(db);
				break;
			case 'n':
				fs.writeFile('db.js',JSON.stringify(db),()=>{
					console.log("Saved.");
					process.exit(0);
				});
				break;
			default:
				done();
				break;
		}
	});
};
var newthing = (curr) => {
	rl.question('What is it? : ', (thing)=>{
		if(thing == null) {
			newthing(curr);
		}else {
			newq(curr, thing);
		}
	});
};

var newq = (curr,thing) => {
	rl.question('Write a question to distinguish "' + thing
		+ '"\nand "' + curr.a + '" : ', (q)=>{
			if(q == null) {
				newq(curr, thing);
			}else {
				newa(curr, thing, q);
			}
	});
};
var newa = (curr, thing, q) => {
	rl .question('What is the answer for "' + thing + '"? (y/n): ', (res) => {
		if(res == 'y'){
			curr.q = q;
			curr.y = {a:thing};
			curr.n = {a:curr.a};
			delete curr.a;
			done();
		}else if(res == 'n') {
			curr.q = q;
			curr.n = {a:thing};
			curr.y = {a:curr.a};
			delete curr.a;
			done();
		} else {
			newa(curr, thing, q);
		} 
	});
}


var ask = (curr)=>{
	if(curr['q'] && curr['q'] != null) {
		rl.question(curr['q'] + ' (y/n): ', (response)=>{
			switch(response) {
				case 'y':
					ask(curr['y']);
					break;
				case 'n':
					ask(curr['n']);
					break;
				default:
					ask(curr);
					break;
			}
		});
	} else if(curr['a'] && curr['a'] != null){
		rl.question('Is it "' + curr['a'] + '"? (y/n): ',(response)=>{
			switch(response) {
				case 'y':
					done();
					break;
				case 'n':
					newthing(curr);	
					break;
				default:
					ask(curr);
					break;
			}	
		});
	}else {
		console.log('Err: ');
		console.log(curr);
		done();
	}
};


