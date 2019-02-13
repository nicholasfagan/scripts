
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

/* endlessly prints fibonacci numbers */

int main() {
	unsigned long long int a=0,b=1,c=0;
	while(1) printf("%llu\n",c=(a=b)+(b=c));
	return 0;
}
