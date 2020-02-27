#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int mod = 1;
int freq_len = 0;
int *freq = NULL;
int dur = 1000;
float inv_scale = 0.1;
typedef unsigned long int ulli;

float square_wave(float time, float note, float scale) {
	return ((ulli)(time * scale) / (ulli)(note)) % 2 ? -1 : 1;
}
float sawtooth_wave(float time, float note, float scale) {
	note++;
return ((ulli)(time * scale) % (ulli)note ) / note;
}
float sin_wave(float time, float note, float scale) {
	return (sawtooth_wave(time,note,scale));
}


//returns a number from 0 to 1 
float wave_form(float time, float note, float scale) {
	return (sin(time*note*scale)+1)/2;
}
void note(ulli n) {
	for(int i = 0; i < dur; i++){
		float sum = 0;
		for(int j = 0; j < freq_len; j++)
			sum += wave_form(i,(freq[j]-n%freq[j]),inv_scale);
		putchar(((sum / freq_len))*127);
	}
}


int main(int argc, char **argv) {
	if(argc < 3) {
		fprintf(stderr,"usage: %s <mod>[,mod[,mod ...]] <note duration> <pitch scale>\n",argv[0]);
		exit(EXIT_FAILURE);
	}


	size_t len_input = strlen(argv[1]);
	char *str = malloc(sizeof(char)*len_input);
	strcpy(str,argv[1]);

	
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
	sscanf(argv[2], "%d", &dur);
	sscanf(argv[3], "%f", &inv_scale);


	ulli input = 0;
	while(1 == scanf("%lu\n",&input)) {
		note(input);
	}

	return EXIT_SUCCESS;

}
