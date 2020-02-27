#include <stdio.h>
#include <stdlib.h>
#include <string.h>


size_t BLEN = 10;

unsigned char *hist;

unsigned char avg(unsigned char *buf, size_t len) {
	unsigned int sum = 0;
	for(size_t i = 0; i < len; i++) {
		sum += buf[i];
	}
	return (unsigned char)( sum / len );
}

//rolling avg
static unsigned char rlavg(unsigned char x) {
	memmove(hist+1,hist,BLEN-1);//forget last byte
	hist[0] = x; //insert the new one
	return avg(hist, BLEN); //return new average
}

void init() {
	hist = malloc(sizeof(unsigned char) * BLEN);
	if(hist == NULL) {
		fprintf(stderr,"blend: error creating buffer.\n");
		exit(1);
	}
	memset(hist, 128, BLEN);
}

int main(int argc, char **argv) {
	if(argc > 1) {
		int res = sscanf(argv[1],"%lu",&BLEN);
		if(res != 1) {
			fprintf(stderr,"blend: error reading arguments.\n");
			exit(1);
		}
	}
	init();
	int c;
	while((c = getchar()) != EOF) {
		putchar(rlavg(c));
	}
	putchar(EOF);
	free(hist);
	return 0;
}

