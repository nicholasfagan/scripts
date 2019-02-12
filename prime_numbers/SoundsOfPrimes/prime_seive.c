#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>
#include <string.h>
int mod = 1;

int freq_len = 0;
int *freq = NULL;
int dur = 1000;
float inv_scale = 0.1;





typedef unsigned long int ulli;
void draw_bits(ulli n) {
	for(int i = 0; i < dur; i++){
		float sum = 0;
		for(int j = 0; j < freq_len; j++)
			sum += sin(i*(freq[j]-n%freq[j])*inv_scale);
		putchar(((sum / freq_len)+1)*127);
	}
/*	
	for(int i = 0; i < dur; i++){
		float sum = 0;
		float count = 0;
		for(int j = 0; j < sizeof(unsigned long int)*4-1; j++) {
			if(n & (1 << j)) {
				sum += sin ( i * j * inv_scale );
				count++;
			}
		}
		if(count == 0) putchar(127);
		else putchar(((sum / count)+1)*127);
	}
	*/
}
void prime_bit_pattern(ulli n) {
	size_t len = 0;
	char *seive = malloc(sizeof(char) * (n+2));
	if(seive == NULL) return;
	for(size_t i = 2; i <= n; i++) seive[i] = 1;
	size_t i;
	for(i = 2; i <= (ulli)floor(sqrt(n)); i++) {
		if(seive[i]) {
			draw_bits(i);
			for(size_t j = i*i; j <= n; j+=i) seive[j] = 0;
		}
	}
	//keep going where last loop left off
	for(;i <= n; i++) if(seive[i]) draw_bits(i);
	free(seive);	
}
int main(int argc, char **argv) {
	if(argc < 5) {
		printf("Error: not enough args.\n");
		return 1;
	}
	ulli n = 0;
	sscanf(argv[1], "%lu", &n);


	//get mods

	size_t len_input = strlen(argv[2]);
	char *str = malloc(sizeof(char)*len_input);
	strcpy(str,argv[2]);

	
	freq_len = 1;
	for(int i = 0; i < len_input; i++) 
		if(str[i] == ','){
			str[i] = 0;
			freq_len++;
		}
	
	freq = malloc(sizeof(int)*freq_len);


	char *pos = str;
	for(int i = 0; i < freq_len; i++) {
		sscanf(pos, "%d", freq+i);
		mod += freq[i];
		while(*pos) pos++;
		pos++;
	}
	sscanf(argv[3], "%d", &dur);
	sscanf(argv[4], "%f", &inv_scale);


	//for(int i = 0; i < n; i++)
		//draw_bits(i);
		prime_bit_pattern(n);
	return 0;
}
