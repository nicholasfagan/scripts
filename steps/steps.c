#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef long long int lli;
typedef unsigned long long int ulli;


ulli fastfib(ulli n) {
	if(n == 0) return 0;
	if(n == 1) return 1;
	ulli k = n/2;
	ulli fk = fastfib(k);
	ulli fk1 = fastfib(k+1);
	return (fk*(2*fk1-fk)) + (fk*fk+fk1*fk1);
}


ulli fib(ulli n) {
	if(n == 0) return 0;
	if(n == 1) return 1;
	return fib(n-1) + fib(n-2);
}

lli steps(lli n) {
	if(n <= 0) return 0;
	else if(n == 1) return 1;
	else if(n == 2) return 2;
	else return steps(n-1) + steps(n-2);
}


int main(void) {
	lli n = 0;
	lli s;
	ulli f;
	ulli ff;
	scanf("%lld", &n);
	s = steps(n);
	printf("Steps : %lld\n",s);
//	f = fib(n+1);
//	printf("Fib   : %llu\n",f);
//	ff = fastfib(n+1);
//	printf("FFib  : %llu\n",ff);
	return 0;
}
