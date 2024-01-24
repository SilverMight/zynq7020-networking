#include "data.h"
#include <stdlib.h>

int * get_n_random_numbers(int n, int upper_bound) {
	int * arr = (int *) malloc(sizeof(int) * n);

	for(int i = 0; i < n; i++) {
		arr[i] = rand() % upper_bound;
	}

	return arr;
}
