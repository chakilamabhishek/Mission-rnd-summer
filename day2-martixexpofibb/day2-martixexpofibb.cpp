// day2-martixexpofibb.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include<stdio.h>

int multiply(int a[2][2],int k,int f[2][1]){
	int res[2][2] = { 0, 1, 1, 1 };
	for (int i = 1; i < k; i++){
		res[0][0] = res[0][0] * a[0][0] + res[0][1] * a[1][0];
		res[0][1] = res[0][0] * a[0][1] + res[0][1] * a[1][1];
		res[1][0] = res[1][0] * a[0][0] + res[1][1] * a[1][0];
		res[1][1] = res[1][0] * a[0][1] + res[1][1] * a[1][1];
	}
	return res[1][0] * f[0][0] + res[1][1] * f[1][0];
}
int main(){
	int A[2][2] = { 0, 1, 1, 1 }, f[2][1] = {0,1};
	printf("%d", multiply(A,4,f));
	getchar();
	return 0;
}

