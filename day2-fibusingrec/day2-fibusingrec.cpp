// day2-fibusingrec.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<math.h>
long mem[100] = { 0 };
long fibb(long n){
	if (n <= 1)
		return n;
	if (mem[n])
		return mem[n];

	mem[n]=fibb(n - 1) + fibb(n - 2);
	return mem[n];
}
int main(){
	for (int i = 1; i < 100; i++){
		printf("fibb of %d %ld\t\t", i,fibb(i-1));
		printf("%lf\n ",round(pow( 1.61803398875,i-1)/sqrt(5.0)));
	}
	getchar();
	return 0;
}

