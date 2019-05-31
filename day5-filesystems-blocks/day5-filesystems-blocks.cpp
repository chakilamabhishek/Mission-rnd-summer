
#include "stdafx.h"
#include<stdio.h>
#include<string.h>
#define no_of_meta_blocks 3
#define size_of_block 16000
#define metadatasize 32
#define metasize 8
#define BUFSIZE 100
int nextblock;

struct metadata{
	char filename[20];
	int start;
	int no_of_blocks;
	int file_length;
};


struct meta{
	int no_of_files;
	int no_of_free_blocks;
};

struct meta previous_data;
int nextslot(char* diskname){
	if(previous_data.no_of_files==0)
		return 1600*(no_of_meta_blocks);
	return metasize + (previous_data.no_of_files + no_of_meta_blocks)*size_of_block;
}


void writemetadataintofile(char *diskname, struct metadata* m1, struct meta* m2){
	FILE *disk = fopen(diskname, "r+");
	if (disk){
		fwrite(m2,sizeof(struct meta),1,disk);
		fseek(disk,metasize+(m2->no_of_files-1)*metadatasize, SEEK_SET);
		//printf("\nwrting meta data at %ld", ftell(disk));
		fwrite(m1, sizeof(struct metadata), 1, disk);
		fclose(disk);
	}
}


void write_into_disk(char* diskname, char *filename){
	int start;
	size_t n;
	struct meta m2;
	struct metadata m1;
	FILE *disk = fopen(diskname, "rb+");
	if (disk){
		start = nextslot(diskname);
		fseek(disk, start, SEEK_SET);
		char buff[BUFSIZE];
		FILE *file = fopen(filename, "rb+");
		if (file == NULL){
			printf("this file %s cannot be opened ", filename);
			return;
		}
		while ((n = fread(buff, 1, BUFSIZE, file)) != 0) {
			printf("n==%d", n);
			fwrite(buff, 1, n, disk);
		}
		m1.file_length = ftell(disk) - start;
		m1.no_of_blocks = (m1.file_length) / size_of_block;
		strcpy(m1.filename, filename);
		m1.start = start;
		m2.no_of_files = previous_data.no_of_files + 1;
		m2.no_of_free_blocks = previous_data.no_of_free_blocks - m1.no_of_blocks;
		previous_data.no_of_files = m2.no_of_files;
		previous_data.no_of_free_blocks = m2.no_of_free_blocks;
		printf("\n no of files :%d free blocks:%d", m2.no_of_files, m2.no_of_free_blocks);
		printf("\nfilename:%s \tfilelength %d \tno_of_blocks %d \tstart address %d \t", m1.filename, m1.file_length, m1.no_of_blocks, m1.start);

		writemetadataintofile(diskname,&m1,&m2);
		fclose(file);
		fclose(disk);
	}
	else
		printf("the file %s cannot be opened", diskname);
}

void write_from_disk(char *diskname,char *filename,char*destination){
	size_t n;
	char buff[BUFSIZE];
	struct meta m2;
	struct metadata m1;
	FILE *disk = fopen(diskname, "rb");
	int count = 0;
	if (disk){
		fread(&m2, sizeof(struct meta), 1, disk);
		//printf("\n no of files :%d free blocks:%d", m2.no_of_files, m2.no_of_free_blocks);
		for (int i = 0; i < m2.no_of_files; i++){
			fseek(disk, metasize + (i)*metadatasize, SEEK_SET);
			fread(&m1, sizeof(struct metadata), 1, disk);
			if(!strcmp(m1.filename, filename)){
				FILE *desti = fopen(destination, "wb");
				fseek(disk, m1.start, SEEK_SET);
				while (count<=m1.file_length){
					fread(buff, 1, 1, disk);
					fwrite(buff, 1, 1, desti);
					count++;
				}
			}
		}
	}
	fclose(disk);
}
void print_meta_data(char *diskname){
	printf("\n in meta dat print\n");
	struct meta m2;
	struct metadata m1;
	FILE *disk = fopen(diskname, "rb");
	if (disk){
		fread(&m2, sizeof(struct meta), 1, disk);
		printf("\n no of files :%d free blocks:%d", m2.no_of_files, m2.no_of_free_blocks);
		/*for (int i = 0; i < m2.no_of_files; i++){
			fseek(disk, metasize + (i)*metadatasize, SEEK_SET);
			fread(&m1, sizeof(struct metadata), 1, disk);
			printf("\nfilename:%s \tfilelength %d \tno_of_blocks %d \tstart address %d \t", m1.filename,m1.file_length,m1.no_of_blocks,m1.start);
		}*/
	}
	fclose(disk);
}
void list_directories(char *diskname){
	if (previous_data.no_of_files == 0){
		return;
	}
	//printf("\n in meta dat print\n");
	struct meta m2;
	struct metadata m1;
	FILE *disk = fopen(diskname, "rb");
	if (disk){
		fread(&m2, sizeof(struct meta), 1, disk);
		//printf("\n no of files :%d free blocks:%d", m2.no_of_files, m2.no_of_free_blocks);
		for (int i = 0; i < m2.no_of_files; i++){
		fseek(disk, metasize + (i)*metadatasize, SEEK_SET);
		fread(&m1, sizeof(struct metadata), 1, disk);
		printf("\nfilename:%s", m1.filename);
		}
	}
	fclose(disk);
}
int main(){
	previous_data.no_of_files = 0;
	char diskname[50] = "disk.hdd";
	FILE *fp = fopen(diskname, "w");
	fclose(fp);
	previous_data.no_of_free_blocks = 6396;
	char str[100],src[100],des[100];
	printf("\n>>>");
	while (scanf_s("%s", str, 50) != EOF){
		switch (str[0]){
		case 'M':
			if (!(strcmp(str, "META")))
			{
				print_meta_data(diskname);
			}
			else
				printf("\nentered a invalid command format");
			break;
		case 'C':
			if (!(strcmp(str, "COPY_INTO_DISK")))
			{
				scanf_s("%s", src, 50);
				write_into_disk(diskname,src);
			}
			else if(!(strcmp(str, "COPY_FROM_DISK"))){
				scanf_s("%s", src, 50);
				scanf_s("%s", des, 50);
				write_from_disk(diskname,src, des);
			}
			else
				printf("\nentered a invalid command format");
			break;
		case 'L':
			if (!(strcmp(str, "LIST")))
			{
				list_directories(diskname);
			}
			else
				printf("\nentered a invalid command format");
			break;
		default :
			printf("no such command\n");
		}
		printf("\n>>>");
		fflush(stdin);
	}
	//write_into_disk("disk.hdd", "one.txt");
	//write_into_disk("disk.hdd", "two.txt");
	//write_into_disk("disk.hdd", "abhi.jpg");
	//print_meta_data("disk.hdd");
	//write_from_disk("disk.hdd", "one.txt", "result.txt");
	//write_from_disk("disk.hdd", "two.txt", "result1.txt");
	//write_from_disk("disk.hdd", "abhi.jpg", "shek.jpg");
	getchar();
	return 0;
}
