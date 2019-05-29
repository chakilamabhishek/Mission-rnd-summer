// day4-sort1Mnumbers-using128KB.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#define len 10000
int no_of_files = 0;
int no_of_results = 0;
FILE *output;
void split(char *filename){
	int count = 0;
	long number;
	char name[len];
	FILE *input, *temp;
	int filenumber = 0;
	input = fopen(filename, "r");
	_itoa(filenumber, name, 10);
	temp = fopen(strcat(name, ".txt"), "w");
	no_of_files++;
	while (fscanf(input, "%ld", &number) == 1){
		count++;
		if (count == 10001){
			count = 0;
			filenumber++;
			_itoa(filenumber, name, 10);
			fclose(temp);
			temp = fopen(strcat(name, ".txt"), "w");
			no_of_files++;
		}
		fprintf(temp, "%ld\n", number);
	}
	fclose(temp);
	fclose(input);
}
int compare(const void * a, const void * b)
{
	return (*(long*)a - *(long*)b);
}
void sort(int filenumber){
	FILE *temp;
	char name[50];
	_itoa(filenumber, name, 10);
	temp = fopen(strcat(name, ".txt"), "r");
	long n = 0, number, arrindex = 0;
	long arr[10002];
	while (fscanf(temp, "%ld", &number) == 1){
		arr[arrindex++] = number;
		//printf("%d\n", number);
		n++;
	}
	fclose(temp);
	name[0] = '\0';
	qsort(arr, n, sizeof(arr[0]), compare);
	_itoa(filenumber, name, 10);
	temp = fopen(strcat(name, ".txt"), "w");
	//printf("----------------");
	for (int i = 0; i < n; i++){
		//printf("%ld \n", arr[i]);
		fprintf(temp, "%ld\n", arr[i]);
	}
	fclose(temp);
}

void merge(int filenumber){
	char name[len];
	_itoa(no_of_results, name, 10);
	no_of_results++;
	FILE *result = fopen(strcat(name, "result.txt"), "w");

	FILE *file2;
	_itoa(filenumber+1, name, 10);
	FILE *file1= fopen(strcat(name, ".txt"), "r");
	if (filenumber== 0){
		_itoa(filenumber, name, 10);
		file2 = fopen(strcat(name, ".txt"), "r");
	}
	else
	{
		_itoa(no_of_results-2, name, 10);
		file2 = fopen(strcat(name, "result.txt"), "r");
	}

	int n1, n2;
	int t1=fscanf(file1, "%ld", &n1);
	int t2=fscanf(file2, "%ld", &n2);
	while (t1==1 && t2==1 ){
		if (n1 <= n2){
			fprintf(result, "%ld\n", n1);
			t1=fscanf(file1, "%ld", &n1);
		}
		else{
			fprintf(result, "%ld\n", n2);
			t2=fscanf(file2, "%ld", &n2);
		}
		
}
	while (t1 == 1){
		fprintf(result, "%ld\n", n1);
		t1=fscanf(file1, "%ld", &n1);
	}
	while (t2 == 1){
		fprintf(result, "%ld\n", n2);
		t2=fscanf(file2, "%ld", &n2);
	}
	fclose(result);
	fclose(file1);
	fclose(file2);
}
int main(){
	split("input.txt");
	for (int i = 0; i < no_of_files; i++)
		sort(i);
	
	for (int i = 0; i < no_of_files-1; i++)
		merge(i);
	printf("==================done===========\n\n");
	getchar();
	return 0;
}

