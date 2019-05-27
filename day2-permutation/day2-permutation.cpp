// day2-permutation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <malloc.h>

void permutate(int *permute, int level, int *a, int n) {
	for (int i = 0; i < level; i++) {
		if (level == 0) {
			break;
		}
		a[level - 1] = permute[i];
		if (level == 1) {
			for (int j = n - 1; j >= 0; j--) {
				printf("%d ", a[j]);
			}
			printf("\n");
		}
		else {
			int *temp = (int *)malloc(sizeof(int) * (level - 1));
			int k = 0;
			for (int j = 0; j < level; j++) {
				if (i != j) {
					temp[k++] = permute[j];
				}
			}
			permutate(temp, level - 1, a, n);
		}
	}
}
int main() {
	int res[4] = { 1, 3, 5 ,4};
	int temp[4];
	permutate(res, 4, temp, 4);
	getchar();
}
