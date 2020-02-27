var readline = require('readline');
var rl = readline.createInterface({
	input: process.stdin,
	output: process.stdout
});

const sum = (acc, curr) => acc + curr;
const fibn = (i, max, prev) => {
	var n = prev.reduce(sum);
	i++;
	if (i >= max)
		return n;
	else {
		prev.shift();//get rid of oldest
		prev.push(n);//add newest
		return fibn(i,max,prev);
	}
}


rl.on('line', (l) => {
	var input = l.split(" ").map((s)=>parseInt(s));
	var n = input.shift();
	console.log(fibn(0,n,input));
});
