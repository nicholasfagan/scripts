
var readline = require('readline');
var rl = readline.createInterface({
	input:process.stdin,
	output:process.stdout
});

const freqarr = (acc, curr) => {
	if(acc.length == 0) {
		acc.push({data:curr,freq:1});
		return acc;
	}
	var index = -1;
	for(var i = 0; i < acc.length; i++) {
		if(acc[i].data == curr) {
			index = i;
			break;
		}
	}
	if(index != -1) {
		acc[index].freq++;
	} else {
		acc.push({data:curr,freq:1});
	}
	return acc;
};
const maxfreq = (acc,curr) => acc.freq < curr.freq ? curr : acc;

rl.on('line', l=>{
	l = l.trim().split(" ").map(n=>parseInt(n));
	console.log(
		l.length
		- l.reduce(freqarr,[])
		.reduce(maxfreq)
		.freq
	);
});

