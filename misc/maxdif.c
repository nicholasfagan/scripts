#include <stdio.h>
#include <limits.h>
/* MaxDif
 * Nick Fagan Dec
 * 2018
 * Calculates max difference between 2 elems 
 * input is number of elements, followed by the elements.
 * output is max difference
 */

int maxdif(size_t len, int arr[len]);

int main(void) {
	size_t len = 0;
	scanf("%lu",&len);
	int arr[len];
	for(size_t i = 0; i < len; i++) {
		scanf("%d",arr+i);
	}
	int res = maxdif(len,arr);
	printf("%d\n",res);
	return 0;
}

int maxdif(size_t len, int arr[len]) {
	if(len == 0 || len == 1) return -1;
	int max = INT_MIN;
	for(size_t i = 1; i < len; i++) {
		if(arr[i]%2==1) continue;
		for(size_t j = 0; j < i; j++) {
			if(arr[i]<=arr[j] || arr[j]%2==0) continue;
			int diff = arr[i]-arr[j];
			if(diff > max) max= diff;
		}
	}
	return (max==INT_MIN?-1:max);
}
