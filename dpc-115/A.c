
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

typedef unsigned long long int ulli;
void swap(unsigned char *arr, int a, int b) {
	unsigned char tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}

int cmp(const void *el1, const void *el2) {
	unsigned char a = *(unsigned char *)el1;
	unsigned char b = *(unsigned char *)el2;
	return a-b;
}

unsigned char *next(unsigned char *n, int pos) {
	
	//find the last non-increasing value from right to left
	int i;
	for(i=pos-1;i>=0;i--) {
		if(n[i]<n[i+1]) {
			//i is pivot
			int j;
			for(j = pos; j>i; j--) {
				//find rightmost succesor to pivot
				if(n[i]<n[j]) {

					//swap them	
//					printf("%s - swap %d %d : ", n, i, j);
					swap(n,i,j);
					//sort the rest
//					printf("%s - sort %d %d : ", n, i+1,pos-i);
					qsort(&n[i+1], pos-i, sizeof(unsigned char),cmp);	
//					printf("%s - ", n);
					return n;
				}
			}
			break;
		}
	}
	//no greater found, add a zero to front and sort rest.
	//then swap first with the next non-zero
	unsigned char *tmp = malloc(sizeof(unsigned char)*(pos+2));
	if(tmp == NULL) return NULL;
	
	strcpy(tmp,n);
	qsort(tmp, pos+1, sizeof(unsigned char),cmp);	
	n = realloc(n,sizeof(unsigned char)*(pos+2));
	if(n==NULL)return NULL;
	n[0]='0';
	strcpy(n+1, tmp);
	free(tmp);
	for(i=1;i<=pos;i++) if(n[i]!='0') {
		swap(n,0,i);
		break;
	}
	return n;
}
int main() {
	size_t count;
	scanf("%ld", &count);
	unsigned char *n = malloc(sizeof(unsigned char)*21);
	if(n == NULL) return 1;
	int i;

	for(i=1;i<=count;i++) {
		scanf("%20s", n);
		int len = strlen(n);
		n = next(n, len-1);
		printf("Case %d: %s\n",i,n);
	}
	return 0;
}
