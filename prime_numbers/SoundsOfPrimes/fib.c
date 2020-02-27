#include <stdio.h>
#include <limits.h>
int main(int argc, char **argv) {
	if(argc > 3 || argc == 1) {
		fprintf(stderr,"usage: %s [term1, term2]",argv[0]);
		return 1;
	}
	unsigned long long int T1=0,T2=1;
	if(argc == 3) {
		sscanf(argv[1],"%llu",&T1);
		sscanf(argv[2],"%llu",&T2);
	}
	while(1) {
		unsigned long long int a=0,b=T1,c=T2;
		while(b+c<( ULLONG_MAX>>1 )) printf("%llu\n",c=(a=b)+(b=c));
	}
	return 0;
}
