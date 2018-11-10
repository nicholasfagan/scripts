#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
typedef unsigned long int ulli;
ulli prime_under(ulli n) {
	size_t len = 0;
	char *seive = malloc(sizeof(char) * (n+2));
	if(seive == NULL) return 0;
	for(size_t i = 2; i <= n; i++) seive[i] = 1;
	for(size_t i = 2; i <= (ulli)floor(sqrt(n)); i++) if(seive[i]) for(size_t j = i*i; j <= n; j+=i) seive[j] = 0;
	for(size_t i = 2; i <= n; i++) if(seive[i]) len++;
	ulli *primes = malloc(len * sizeof(ulli));
	if(primes == NULL) {
		free(seive);
		return 0;
	}
	for(size_t i = 2, j = 0; i <= n && j < len; i++) if(seive[i]) primes[j++] = i;
	free(seive);
	ulli res = primes[len - 1];
	free(primes);
	return res;
}
int main(int argc, char **argv) {
	if(argc < 2) {
		printf("Error: not enough args.\n");
		return 1;
	}
	ulli n = 0;
	sscanf(argv[1], "%lu", &n);
	printf("%lu\n", prime_under(n));
	return 0;
}
