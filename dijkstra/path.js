const fs = require('fs');
const printBoard = (b)=>{
	const blockchar = '\u2588';
	var str = '';
	for(var i = 0; i < b[0].length + 2; i++) str += blockchar;
	str += '\n';
	b.forEach(r=>{
		str += blockchar;
		r.forEach(c=>str+=(c?blockchar:' '));
		str+=blockchar + '\n';
	});
	for(var i = 0; i < b[0].length + 2; i++) str += blockchar;
	console.log(str);
};
const printSol = (b,s)=>{
	const blockchar = '\u2588';
	const step = '*'
	var str = '';
	for(var i = 0; i < b[0].length + 2; i++) str += blockchar;
	str += '\n';
	for(var i = 0; i < b.length; i++) {
		str += blockchar;
		for(var j = 0; j < b[i].length; j++) {
			str+= b[i][j] ? blockchar : ( posIndex(s,{x:j,y:i}) != -1 ? posIndex(s,{x:j,y:i})%10 : ' ' );
		}
		str+=blockchar + '\n';
	}
	for(var i = 0; i < b[0].length + 2; i++) str += blockchar;
	console.log(str);
};
const posIndex = (list,pos) => {
	for(var i = 0; i < list.length; i++)
		if(list[i].x == pos.x && list[i].y == pos.y)
			return i;
	return -1;	
};
const posin = (list,pos) => {
	return posIndex(list,pos) != -1;
};
const getAdj = (b,p) => {
	if(!p || !b) return [];
	const Xmax = b[0].length-1;
	const Ymax = b.length-1;
	var res = [];
	if(p.x != 0)    res.push({x:p.x-1,y:p.y,prev:p,d:p.d+1});
	if(p.x != Xmax) res.push({x:p.x+1,y:p.y,prev:p,d:p.d+1});
	if(p.y != 0)    res.push({x:p.x,y:p.y-1,prev:p,d:p.d+1});
	if(p.y != Ymax) res.push({x:p.x,y:p.y+1,prev:p,d:p.d+1});
	return res.filter(el=>!b[el.y][el.x]);
};
const psort = (a,b) => {
	var m = a.y-b.y;
	m = m != 0 ? m : a.x-b.x;
	m = m != 0 ? m : a.d-b.d;
	return m;
};
const dsort = (a,b) => a.d-b.d;
const minDist = (list, el) => {
	//assume list is sorted by psort
	if(list.length == 0 || list[list.length-1].x != el.x || list[list.length-1].y != el.y) list.push(el);
	return list;
}
const mst = (b, start) => {
	start.d = 0;
	var confirmed = [];
	var unsolved = [start];
	while(unsolved.length > 0) {
		//remove confirmed, sort by position, remove duplicate, sort by distance
		unsolved = unsolved
			.sort(psort)
			.reduce(minDist,[])
			.sort(dsort);
		//take the lowest distance, its confirmed.
		confirmed.push(unsolved.shift());
		//get new neighbors
		confirmed.forEach(p=>
			getAdj(board,p)
			.forEach(np=>{
					if(!posin(confirmed,np))
						unsolved.push(np);
			})
		);
	}
	return confirmed;
};
const pathTo = (tree,end) => {
	var curr = tree.filter(el=>el.x == end.x && el.y == end.y)[0];
	if(!curr) return [];
	var path = [{x:curr.x,y:curr.y}];
	while(curr.prev) {
		path.unshift({x:curr.prev.x,y:curr.prev.y});
		curr = curr.prev;
	}
	return path;
};


var board = JSON.parse(fs.readFileSync('board.js'));
var start = {x:0,y:0};
var minSpanTree = mst(board, start);
var path = pathTo(minSpanTree, {x:board[0].length-1,y:board.length-1});
console.log('%d steps', path.length-1);
printSol(board,path);

