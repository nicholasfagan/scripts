/** NthPrime Generator
  * Uses some math to calculate an upper bound for the size of the prime
	* then using a prime seive, generates the nth prime.
	*
	* Nick Fagan
	* Fall 2018
  */


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "seive.h"

typedef unsigned int ulli;

ulli get_upper_bound(ulli n);

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
	
	//get input
	size_t len = 0;
	ulli n = 0;
	sscanf(argv[argc - 1], "%u", &n);

	//calc upper bound
	ulli bound = get_upper_bound(n);
	if(verbose) printf("Upper bound: %u\n", bound);
	
	//generate seive
	ulli *primes = prime_seive(bound, &len);

	if(verbose > 1) for(size_t i = 0; i < len; i++) printf("%u\n", primes[i]);
	if(verbose) printf("Generated %lu primes up to %u\nPrime #%u is ", len, bound, n);
	
	//select nth prime
	printf("%u\n", primes[n-1]);
	
	//cleanup
	free(primes);	
	return 0;
}

// Calculates a loose upper bound for pi(n)
// AKA the number of primes less than n.
// Uses some math deciphered from wikipedia.
ulli get_upper_bound(ulli n) {
	if(n < 6) return 20;
	else return ceil(n*log(n*log(n)));
}


