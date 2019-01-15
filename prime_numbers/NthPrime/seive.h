
#ifndef PRIME

#define ISPRIME 1
#define NOTPRIME 0


typedef unsigned int ulli;

ulli *prime_seive(ulli max, size_t *len);



// Prime Sieve, that creates an array of primes up to max.
// the new array has size len.
ulli *prime_seive(ulli max, size_t *len) {
	//allocate and initialize seive
	char *seive = malloc((max+4)*sizeof(char));
	if(seive == NULL) return NULL;
	for(ulli i = 2; i <= max; i++) seive[i] = ISPRIME;
	//go through seive
	for(ulli i = 2; i <= (ulli) floor(sqrt(max)); i++) {
		if(seive[i] == ISPRIME) {
			for(ulli j = i*i; j <= max; j += i) {
				seive[j] = NOTPRIME;
			}
		}
	}
	//count
	(*len) = 0;
	for(ulli i = 2; i <= max; i++) if(seive[i] == ISPRIME) (*len)++;
	//allocate
	ulli *primes = malloc((*len + 2) * sizeof(ulli));
	if(primes == NULL) return NULL;
	//add to list
	size_t i = 0;
	for(ulli j = 2; j <= max && i < *len; j++) if(seive[j] == ISPRIME) primes[i++] = j;
	free(seive);
	return primes;
}

#endif
