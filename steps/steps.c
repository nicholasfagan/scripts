#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef long long int lli;
typedef unsigned long long int ulli;

ulli fib(ulli n) {
	if(n == 0) return 0;
	if(n == 1) return 1;
	return fib(n-1) + fib(n-2);
}
int main(void) {
	size_t num;
	scanf("%lu", &num);
	ulli st = fib(num+1,s);
	printf("Steps : %lld\n",st);
	return 0;
}
