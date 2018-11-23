
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

unsigned char *next(unsigned char *arr, int len) {
	if(len == 0) return NULL;
	int i = len-1,j=0;
	while(i>0 && arr[i-1] >= arr[i]) i--;
	//now i is index of pivot, the digit that needs changing.
	if(i == 0) {
//		printf("Adding 0 - ");
		//there is no pivot, 
		//add a zero after the first char
		unsigned char *new = malloc(sizeof(unsigned char)*(len+2));
		if(new == NULL)return NULL;
		new[0]=arr[0];
		new[1]='0';
		strcpy(new+2,arr+1);
		free(arr);
		arr=new;
		i=2;
		len++;
	}else {
		//find rightmost successor
		j = len-1;
		while(arr[j] <= arr[i-1]) j--;

//		printf("swap %d,%d - ", i-1,j);
		//now j is the rightmost successor of i
		swap(arr,i-1,j);
		//swap them
	}
		//then reverse suffix
		//its in order up until pivot
		j=len-1;
//		printf("sort %d,%d - ",i,j);
		while(i<j)
			swap(arr,i++,j--);
		return arr;
}
int main() {
	size_t count;
	scanf("%ld", &count);
	unsigned char *n = malloc(sizeof(unsigned char)*22);
	if(n == NULL) return 1;
	int i;

	for(i=1;i<=count;i++) {
		scanf("%21s", n);
		int len = strlen(n);
		n = next(n, len);
		printf("Case %d: %s\n",i,n);
	}
	return 0;
}
