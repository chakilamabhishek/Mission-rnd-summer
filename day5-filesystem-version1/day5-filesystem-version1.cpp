// day5-filesystem-version1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<string.h>
int no_files = 0;
long metadatasize = 1000;
struct metadata{
	char filename[16];
	long start;
	long length;
};
int nextslot(char *diskname){
	if (no_files == 0)
		return metadatasize;

	FILE *disk = fopen(diskname, "r");
	if (disk==NULL)
	{
		printf("the file %s cannot be opened", diskname);
		return -1;
	}
	struct metadata input;
	fseek(disk,16,SEEK_SET);
	input.start = 0;
	input.length = 0;
	long lastslot;
	int i;
	for (i = 0; i < no_files; i++){
		fseek(disk, 16 + 32 * i, SEEK_SET);
		int x = fread(&input, sizeof(struct metadata), 1, disk);
		printf("ftell at nextslot %d", ftell(disk));
		if (x == -1){
			printf("data cannot be read from %s", diskname);
			return -1;
		}
		else{
			printf("\ndata ininout %d====%d\n", input.start, input.length);
		}
	}
	lastslot =input.length;
	return lastslot + 100;
}
void writemetadataintofile(char *diskname,struct metadata *temp){
	FILE *disk = fopen(diskname, "r+");
	if (disk==NULL)
	{
		printf("the file %s cannot be opened", diskname);
		return;
	}
	
	fseek(disk, 16+32*no_files, SEEK_SET);
	struct metadata input;
	printf("while writing the metadata ftell %ld", ftell(disk));
	int x=fwrite(temp, sizeof(struct metadata), 1, disk);
	if (x == -1){
		printf("data cannot be read from %s", diskname);
		return;
	}
	fclose(disk);
}
void copyintodisk(char* diskname, char*filename){
	struct metadata input;
	char ch;
	FILE *file = fopen(filename, "r");
	if (file==NULL)
	{
		printf("the file %s cannot be opened", filename);
		return;
	}
	int start = nextslot(diskname);
	FILE *disk = fopen(diskname, "r+");
	if (disk==NULL)
	{
		printf("the file %s cannot be opened", diskname);
		return;
	}
	fseek(disk, start, SEEK_SET);
	while ((ch = fgetc(file)) != EOF){
		printf("%c is written at %ld\n", ch, ftell(disk));
		fprintf(disk, "%c", ch);
	}
	input.length = ftell(disk);
	strcpy(input.filename, filename);
	input.start = start;
	fclose(disk);
	fclose(file);
	writemetadataintofile(diskname,&input);
	printf("\n%s ==copied successfully\n", filename);
	no_files++;
	disk = fopen("disk.hdd", "r+");
	if (disk==NULL)
	{
		printf("the file %s cannot be opened", diskname);
		return ;
	}
	printf("\nit shouls be zero %ld,no of files %d",ftell(disk),no_files);
	fprintf(disk, "%d", no_files);
}
void copyfromdisk(char * diskname, char*filename,char *destination){
	FILE *disk = fopen(diskname, "r+");
	char ch;
	struct metadata input;
	if (disk == NULL)
	{
		printf("the file %s cannot be opened", diskname);
		return;
	}
	fseek(disk, 16, SEEK_SET);
	FILE *dest = fopen(destination, "w");
	if (disk == NULL)
	{
		printf("the file %s cannot be opened", destination);
		return;
	}
	for (int i = 0; i < no_files; i++){
		fseek(disk, 16 + 32 * i, SEEK_SET);
		int x = fread(&input, sizeof(struct metadata), 1, disk);
		if (strcmp(input.filename,filename)){
			fseek(disk,input.start, SEEK_SET);
			for (int j = 0;j<input.length-input.start; j++){
				ch = fgetc(disk);
				fprintf(dest, "%c", ch);
			}
			return;
		}
	}
	
	fclose(disk);
	fclose(dest);
}
void listallfiles(char *filename){
	struct metadata input;
	FILE *disk = fopen(filename, "r");
	if (disk==NULL)
	{
		printf("the file %s cannot be opened", filename);
		return ;
	}
	fseek(disk, 16, SEEK_SET);
	for (int i = 0; i < no_files; i++){
		fseek(disk, 16 + 32 * i, SEEK_SET);
		int x=fread(&input, sizeof(struct metadata), 1, disk);
		if (x == -1){
			printf("data cannot be read from %s", filename);
			return;
		}
		printf("\nfilename = %s \t filestart = %u \t fileend = %u \n", input.filename, input.start, input.length);
	}
}
int main(){ 
	copyintodisk("disk.hdd","0.txt");
	copyintodisk("disk.hdd", "1.txt");
	copyintodisk("disk.hdd", "abhi.jpg");
	copyintodisk("disk.hdd", "1.txt");
	copyintodisk("disk.hdd", "0.txt");
	/*char *filename = "disk.hdd";
	FILE *disk = fopen(filename, "r+");
	if (disk==NULL)
	{
		printf("the file %s cannot be opened", filename);
		return 0;
	}
	fscanf(disk,"%d",&no_files);*/
	printf("no of files are %d", no_files);
	listallfiles("disk.hdd");
	char exportfile[100],destination[100];
	printf("enter output file name and destination\n");
	scanf("%s %s", &exportfile,&destination);
	copyfromdisk("disk.hdd", exportfile, destination);


	printf("enter output file name and destination\n");
	scanf("%s %s", &exportfile, &destination);
	copyfromdisk("disk.hdd", exportfile, destination);

	printf("enter output file name and destination\n");
	scanf("%s %s", &exportfile, &destination);
	copyfromdisk("disk.hdd", exportfile, destination);
	getchar();
	return 0;
}
