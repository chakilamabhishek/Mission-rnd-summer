// day3-maze-v1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
int count =0;
int summatrix(int a[100][100],int n,int m){
	int sum = 0;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++)
			sum += a[i][j];
	}
	return sum;
}
void findpath(int matrix[100][100],int starti,int startj,int endi,int endj,int n,int m,int path[100][100],int best[100][100]){
	path[starti][startj] = 1;
	/*printf("path ->(%d , %d ) \n",starti,startj);
	/*printf("\n");
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 9; j++){
			printf("%d", path[i][j]);
		}
		printf("\n");
	}*/
	if (starti == endi && startj == endj){
		path[starti][startj] = 1;
		count++;
		printf("\n\n solution %d\n\n",count);
		for (int i = 0; i < n; i++){
			for (int j = 0; j < m; j++){
				printf("%d", path[i][j]);
			}
			printf("\n");
			
		}
		if (summatrix(best,n,m) > summatrix(path,n,m)){
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					best[i][j] = path[i][j];
		}
		path[starti][startj] = 0;
		return ;
	}
	else{
		
		int diri ,dirj;
		for (diri = -1; diri <=1; diri++){
			for (dirj = -1; dirj<= 1; dirj++){
				if (abs(diri) != abs(dirj) && !(diri == 0 && dirj == 0))
				{
					if (starti + diri >= 0 && starti + diri < n &&startj + dirj >= 0 && startj + dirj < m && matrix[starti + diri][startj + dirj] == 1&&path[starti+diri][startj+dirj]==0){
						findpath(matrix, starti + diri, startj + dirj, endi, endj, n, m, path,best);
						//if (findpath(matrix,starti+diri,startj+dirj,endi,endj,n,m,path))
							//return true;
					
					}
				}
			}
		}
		path[starti][startj] = 0;
	}
	return;
}

int main(){
	int matrix[100][100] = { 
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 1, 0, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 0, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 0, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	};
	int path[100][100] = { 0 };
	path[0][0] = 1;
	int best[100][100];
	int n = 7, m = 7;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			best[i][j] = 1;
	findpath(matrix, 0, 0, 6, 6, n, m, path,best);
	/*if (findpath(matrix, 0, 0, 8, 9, 9,10, path)){
		printf("\n");
		for (int i = 0; i < 8; i++){
			for (int j = 0; j < 9; j++){
				printf("%d", path[i][j]);
			}
			printf("\n");
		}
	}*/
	printf("all possible solutions are done..");

	printf("\n\n**best path is **\n");
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++)
			printf("%d ", best[i][j]);
			printf("\n");
	}
	getchar();
	return 0;
}

