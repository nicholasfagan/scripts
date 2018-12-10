var util = require('util');
var readline = require('readline');

var stdin = process.stdin;
stdin.setRawMode(true);
stdin.resume();
stdin.setEncoding('utf8');

var WIDTH=80,HEIGHT=20;
var score = [0,0];
var frametime = 100;
var speedup = () => {
	frametime = Math.ceil(frametime*0.8);
}; 


var dbox = () => {
	atc(0,0,' ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~');

	atc(0,HEIGHT,' ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~');
};

var cline = () => {
	for(var h = 2; h < HEIGHT; h+=2) atc(WIDTH/2,h,'|');
};





var clear = () => process.stdout.write('c');
var move = (x,y) => process.stdout.write(util.format('[%d;%dH',Math.floor(y),Math.floor(x)));
var home = () => move(0,0);
var atc = (x,y,c) => {
	move(x,y);
	process.stdout.write(c);
};

var intro = (cb,t) => {
	clear();
	home();
	setTimeout(()=>{
		move(WIDTH/2-1,HEIGHT/2);
		setTimeout(()=>{
			process.stdout.write('P');
			setTimeout(()=>{
				process.stdout.write('O');
				setTimeout(()=>{
					process.stdout.write('N');
					setTimeout(()=>{
						process.stdout.write('G');
						setTimeout(()=>{
							cb();
						},t);

					},t);

				},t);

			},t);

		},t);
	},t);
};

var cleanexit = () => {
	home();
	clear();
	process.exit();	
};

var lose = (s) => {
	clear();
	atc(WIDTH/2-7,HEIGHT/2-1,s + ' Lost!');
	move(0,23);
	process.exit();
};
var drawscore = () => {
	atc(WIDTH/2-4,HEIGHT+2,' ' + score[0]);
	atc(WIDTH/2,HEIGHT+2,'|');
	atc(WIDTH/2+2,HEIGHT+2,' ' + score[1]);
};
var point = (p) => {
	score[p]++;
	if(score[0] >= 10) lose('Player 2');
	else if(score[1] >= 10) lose('Player 1');
	drawscore();
	home();

	atc(x,y,' ');
	 x = 3;
	 y = 3;
	 xv = 2;
	 yv = 1;
	nopaddle(0,p1);
	nopaddle(WIDTH,p2);
	 p1 = HEIGHT/2;
	 p2 = HEIGHT/2;
	atc(x,y,'O');
	paddle(0,p1);
	paddle(WIDTH,p2);
};
var init = (cb) => {
	home();
	clear();
	dbox();
	cline();
	drawscore();
	home();
	if(cb)cb();
};




var loop = (f, tf) => {
	var g = () => {
		f();
		setTimeout(g,tf());
	}
	setTimeout(g,tf());
};
const PH = 3;
var nopaddle = (x,y) => {
	atc(x,y-1,' ');
	atc(x,y,' ');
	atc(x,y+1,' ');
}
var paddle = (x,y) => {
	atc(x,y-1,'|');
	atc(x,y,'|');
	atc(x,y+1,'|');
};
var currframetime = () => {
	return frametime;
};

	var x = 3;
	var y = 3;
	var xv = 2;
	var yv = 1;
	var p1 = HEIGHT/2;
	var p2 = HEIGHT/2;

intro(()=>init(()=>{
	 x = 3;
	 y = 3;
	 xv = 2;
	 yv = 1;
	 p1 = HEIGHT/2;
	 p2 = HEIGHT/2;
	atc(x,y,'O');
	paddle(0,p1);
	paddle(WIDTH,p2);
	stdin.on('data',k=>{
		if(k==='\u0003') {
			//CTRL-c
			cleanexit();
		}
		else if(k==='\u0004') {
			//CTRL-d
			cleanexit();
		}
		var dp1 = (k==='w'?-1:(k==='s'?1:0));
		var dp2 = (k==='i'?-1:(k==='k'?1:0));
		if(dp1 != 0) {
			nopaddle(0,p1);
			paddle(0,p1+=dp1);
			home();
		}else if(dp2 != 0) {
			nopaddle(WIDTH,p2);
			paddle(WIDTH,p2+=dp2);
			home();
		}
	});
	loop(()=>{
		if(x+xv < 2 && xv < 0){
			if(p1-1 <= y && y <= p1+1){
				if(p1==y)speedup(); 
				xv *= -1;
				yv = (y-p1 == 0 ? yv : y-p1);
			}
			else point(1);
		}
		if(x+xv > WIDTH -1  && xv > 0){
			if(p2-1 <= y && y <= p2+1) {
				if(p2==y) speedup();
				xv *= -1;
				yv = (y-p2 == 0 ? yv : y-p2);
			}
			else point(0);
		}
		if(y+yv <= 1 || HEIGHT-1 < y+yv) yv *= -1;
		atc(x,y,' ');
		x+=xv;
		y+=yv;
		atc(x,y,'O');
		if(x-xv == WIDTH/2) cline();
		home();
	},currframetime);
}),500);
