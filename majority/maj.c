#include <stdio.h>
int main(int argc, char** argv){
	if(argc != 2) {
		fprintf(stderr, "usage: %s <number>\n",argv[0]);
		return 1;
	}
	int x = atoi(argv[1]);
	char m[x];
	memset(m, 0, x);
	m[0] = getchar();
	unsigned long long int n[x];
	memset(n, 0, x);
	int c; 
	while((c=getchar()) != EOF){
		int found = 0;
		for(int i = 0; i < x; i++) {
			if(m[i] == c) {
				n[i]++;
				found = 1;
				break;
			}
		}
		if(found) continue;
		for(int i = 0; i < x; i++) {
			if(n[i] == 0) {
				n[i] = 1;
				m[i] = c;
				found = 1;
				break;
			}
		}
		if(found) continue;
		for(int i = 0; i < x; i++) {
			n[i]--;
		}
	}
	for(int i = 0; i < x; i++)
		putchar(m[i]);
}
