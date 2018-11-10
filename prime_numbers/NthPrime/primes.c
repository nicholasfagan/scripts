#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
typedef unsigned int ulli;
ulli get_upper_bound(ulli n) {
	if(n < 6) return 20;
	else return ceil(n*log(n*log(n)));
}
ulli *prime_seive(ulli max, size_t *len) {
	//allocate and initialize seive
	char *seive = malloc((max+4)*sizeof(char));
	if(seive == NULL) return NULL;
	for(ulli i = 2; i <= max; i++) seive[i] = 1;
	//go through seive
	for(ulli i = 2; i <= (ulli) floor(sqrt(max)); i++) if(seive[i] == 1) for(ulli j = i*i; j <= max; j += i) seive[j] = 0;
	//count
	(*len) = 0;
	for(ulli i = 2; i <= max; i++) if(seive[i] == 1) (*len)++;
	//allocate
	ulli *primes = malloc((*len + 2) * sizeof(ulli));
	if(primes == NULL) return NULL;
	//add to list
	size_t i = 0;
	for(ulli j = 2; j <= max && i < *len; j++) if(seive[j] == 1) primes[i++] = j;
	free(seive);
	return primes;
}
int main(int argc, char **argv) {
	if(argc < 2) {
		printf("usage: nthprime [options] <n>\n");
		return 0;
	}

	//get arguments
	int verbose = 0;
	for(int i = 1; i < argc-1; i++) {
		if( (strlen(argv[i]) > 1) &&
				argv[i][0] == '-' &&
				argv[i][1] == 'v')
			verbose++;
	}
	size_t len = 0;
	ulli n = 0;
	sscanf(argv[argc - 1], "%u", &n);
	ulli bound = get_upper_bound(n);
	if(verbose) printf("Upper bound: %u\n", bound);
	ulli *primes = prime_seive(bound, &len);
	if(verbose > 1) for(size_t i = 0; i < len; i++) printf("%u\n", primes[i]);
	if(verbose) printf("Generated %lu primes up to %u\nPrime #%u is ", len, bound, n);
	printf("%u\n", primes[n]);
	free(primes);	
	return 0;
}
