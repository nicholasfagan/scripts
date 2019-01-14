




var readline = require('readline');
var rl = readline.createInterface({
	input:process.stdin,
	ooutput:process.stdout
});


const minimum = (a,c)=>a<c?a:c;
const maximum = (a,c)=>a>c?a:c;

var sol = (S,E) => {
	var min = S.reduce(minimum);
	var max = E.reduce(maximum);

	var arr = Array.from({length:max-min},()=>0);
	for(var i = 0; i < S.length; i++) {
		for(var j = S[i]; j < E[i]; j++) arr[j-min]++;
		console.log(S[i],E[i],arr);
	}
	return arr.reduce(maximum);
} 
rl.on('line',l=>{
var s = [1,2,6,5,3];
	var e = [5,5,7,6,8];
	console.log(sol(s,e));
});
