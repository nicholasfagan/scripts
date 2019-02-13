#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
typedef unsigned long int ulli;
void prime_seive(ulli n) {
	size_t len = 0;
	char *seive = malloc(sizeof(char) * (n+2));
	if(seive == NULL) return;
	for(size_t i = 2; i <= n; i++) seive[i] = 1;
	size_t i;
	for(i = 2; i <= (ulli)floor(sqrt(n)); i++) {
		if(seive[i]) {
			printf("%lu\n",i);
			for(size_t j = i*i; j <= n; j+=i) seive[j] = 0;
		}
	}
	//keep going where last loop left off
	for(;i <= n; i++) if(seive[i]) printf("%lu\n",i);
	free(seive);	
}
int main(int argc, char **argv) {
	if(argc < 2) {
		printf("usage: %s <max size>\n",argv[0]);
		return 1;
	}
	ulli n = 0;
	sscanf(argv[1], "%lu", &n);
		prime_seive(n);
	return 0;
}
