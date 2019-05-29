// day4-sort1Mnumbers-usingbitmap-128KB.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include<stdio.h>
struct node{
	int x : 1;
}bitmap[1000000];
int main(){
	long int i, n1,count=0;
	
	for (int k = 0; k < 10; k++){
		FILE *fp = fopen("input.txt", "r");
		while (fscanf(fp, "%ld", &n1) == 1){
			if (n1 < 1000000*(k+1))
				bitmap[n1%1000000].x = 1;
		}
		for (i = 0; i < 1000000; i++){
			if (bitmap[i].x){
				printf("%ld\n", i + 1000000 * k);
				bitmap[i].x = 0;
			}
		}
		fclose(fp);
	}
	getchar();
	return 0;
}

