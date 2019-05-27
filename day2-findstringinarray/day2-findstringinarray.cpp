// day2-findstringinarray.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
int check(char a[5][5], int diri, int dirj,char *word,int i,int j,int n,int m){
	int k=1;
	i = diri + i;
	j = dirj + j;
	while (word[k]!='\0'&&i>=0&&i<n&&j>=0&&j<m)
	{
		if (word[k] == a[i][j])
		{
			k = k + 1;
			i = diri + i;
			j = diri + j;
		}
		else
			break;
	}
	if (word[k] == '\0')
		return 1;
	return 0;
}
void find(char a[5][5],int i,int j,int n,int m,char *word,int lw){
	int y,z,temp1,temp2;
	for (y = -1; y <= 1; y++) {
		for (z = -1; z <= 1; z++) {
			if (i + y >= 0 && i + y < n&&j + z>= 0 && j + z < m && (!( y == 0 && z == 0))){
				//printf("\n posible direction form found are %d %d", i+y, j+z);
				if (check(a,y,z,word,i,j,n,m)){
					printf("string found from (%d,%d)", i, j);
					printf("--to (%d,%d)\n", i + y*lw, j + z*lw);
				}
			}
		}
	}
}
void search(char a[5][5], int n, int m,char*word,int lw) {
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			if (a[i][j] == word[0]){
				//printf("first char found at %d %d", i, j);
				if (lw!=0)
				find(a, i, j, n, m, word, lw);
				else{
					printf("string found from (%d,%d)-- to(%d,%d)\n", i, j, i, j);
				}
			}
		}
	}
}
int main(){
	char a[5][5] = {
		{'e','e','e','e','e'},
		{'e','e','e','e','e'},
		{'e','e','e','e','e'},
		{'e','e','e','e','e'},
		{'e','e','e','e','e'}
	};
	char str[5] = {'e','\0'};
	search(a, 5, 5, str, 0);
	getchar();
	return 0;
}