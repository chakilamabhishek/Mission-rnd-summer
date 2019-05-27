// day2-nstepsclimb.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>

long noofsteps(int n,int k){
	int i, noofways=0;
	if (n <=0)
		return 0;
	for (i = 1; i <= k; i++){
		noofways += noofsteps(n - i, k)+1;
	}
	return noofways;
}


int main(){
	printf("%ld", noofsteps(5, 2));
	getchar();
	return 0;
}
