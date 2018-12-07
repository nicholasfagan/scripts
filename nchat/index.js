var inquirer = require('inquirer');
var client = require('./client.js');
var server = require('./server.js');
var questions = [
	{
		type: 'list',
		name:'app',
		message:'Client or Server :',
		choices: ['Client','Server']
	},
	{
		type: 'input',
		name: 'host',
		default: 'localhost',
		message: 'Server Hostname :',
	},
	{
		type: 'input',
		name: 'port',
		default: 8080,
		message: 'Server Port :',
		filter: (input) => {
			return parseInt(input);
		},
		validate: (input) => {//test is valid port
			var p = parseInt(input);
			if (Number.isInteger(p)
				&& 0 < p
				&& p < 65536)
				return true;
			else return '0 < Port < 65536';
		}
	},
	{
		type: 'input',
		name: 'alias',
		message: 'Your Name :',
		validate: (input) => {
			if((input || '') != '') {
				if(input.indexOf(' ')!==-1)
					return 'No spaces allowed.';
				else 
					return true;
				return 'Required';
			}
		},
		when: (ans) => {
			return ans.app == 'Client';
		}
	}
];
inquirer.prompt(questions).then(function(ans) {
	if(ans.app=='Server') {
		server.run(ans.host, ans.port);
	} else {
		client.run(ans.host, ans.port, ans.alias);
	}
});
