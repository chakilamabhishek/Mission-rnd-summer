// day2print.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>

void print(int *arr,int n){
	int flag = 0;
	for (int i = 0; i < n; i++)
		if (arr[i] || flag){
			printf("%d", arr[i]);
			flag = 1;
		}
	printf("\n");
}

void pattern(int *arr,int currentstate,int n){
	int i;
	if (currentstate <n){
		for (i = 0; i <= 9; i++){
			arr[currentstate] = i;
			pattern(arr, currentstate + 1, n);
			if (currentstate+1==n)
			print(arr,n);
		}
		arr[currentstate] = 0;
	}
}
int main(){
	int arr[10];
	pattern(arr,0,3);
	getchar();
	return 0;
}

