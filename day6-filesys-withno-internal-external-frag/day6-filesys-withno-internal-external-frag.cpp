
#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define no_of_meta_blocks 1
#define size_of_block 16384
#define metadatasize 32
#define metasize 12
#define BUFSIZE 16384
int no_of_blocks_used = 0;

int readdatafromdisk(char *diskname, int blocknumber, void *buff);
void writedatatofile(char *diskname, int blocknumber, void *buff);

struct metadata{
	char filename[20];
	int start_block;
	int no_of_blocks;
int file_length;
};


struct meta{
	int magicnumber;
	int no_of_files;
	int no_of_free_blocks;
};

struct meta previous_data;
int nextslot(char* diskname){
	struct meta m2;
	struct metadata m1;
	int nextblock;
	void* buff = malloc(size_of_block);
	readdatafromdisk(diskname, 0, buff);
	memcpy(&m2, buff, sizeof(struct meta));
	if (previous_data.no_of_files == 0)
		return no_of_meta_blocks;
	for (int i = 0; i < m2.no_of_files; i++){
		memcpy(&m1, (char*)buff + metasize + (i)*metadatasize, sizeof(struct metadata));
		nextblock = m1.start_block + m1.no_of_blocks;
	}
	return nextblock;
}

void writemetadataintofile(char *diskname, struct metadata* m1, struct meta* m2){

	//void* buff = malloc(size_of_block);
	//readdatafromdisk(diskname, 0, buff);
	//memcpy(buff, &m2, sizeof(struct meta));

	//memcpy((char*)buff + metasize + (m2->no_of_files - 1)*metadatasize, &m1, sizeof(struct metadata));
	//writedatatofile(diskname,0,buff);
	FILE *disk = fopen(diskname, "r+");
	if (disk){
		fwrite(m2, sizeof(struct meta), 1, disk);
		if (m2->no_of_files == 1)
			m2->magicnumber = 0x444E524D;
		fseek(disk, metasize + (m2->no_of_files - 1)*metadatasize, SEEK_SET);
		//printf("\nwrting meta data at %ld", ftell(disk));
		fwrite(m1, sizeof(struct metadata), 1, disk);
		fclose(disk);
	}
}

int readdatafromdisk(char *diskname, int blocknumber, void *buff){
	FILE *disk = fopen(diskname, "rb");
	if (disk){
		int n = fseek(disk, blocknumber*size_of_block, SEEK_SET);
		fread(buff, 1, BUFSIZE, disk);
		fclose(disk);
		return n;
	}
	else
		printf("the file %s cannot be opened", diskname);
	return -1;
}

void writedatatofile(char *diskname, int blocknumber, void *buff){
	FILE *disk = fopen(diskname, "rb+");
	if (disk){
		int n = fseek(disk, blocknumber*size_of_block, SEEK_SET);
		fwrite(buff, 1, BUFSIZE, disk);
		fclose(disk);
		return;
	}
	else
		printf("the file %s cannot be opened", diskname);
	return;
}


void write_into_disk(char* diskname, char *filename){
	int start;
	int i = 0;
	size_t n;
	struct meta m2;
	struct metadata m1;
	int metaindex = 0;
	char meta[size_of_block],*temp=(char*)malloc(10*sizeof(char));


	void* buff = malloc(size_of_block);
	readdatafromdisk(diskname, 0, buff);
	memcpy(&m2, buff, sizeof(struct meta));
	start = nextslot(diskname);

	FILE *file = fopen(filename, "rb+");
	if (file == NULL){
		printf("this file %s cannot be opened ", filename);
		return;
	}


	fseek(file, 0, SEEK_END);
	int file_length = ftell(file);
	fseek(file, 0, SEEK_SET);

	if ((file_length / size_of_block) == 0){

		while ((n = fread(buff, 1, BUFSIZE, file)) != 0) {
			writedatatofile(diskname, start + i, buff);
			i++;
			//fwrite(buff, 1, n, disk);
		}


		m1.file_length = ftell(file);
		m1.no_of_blocks = i;
		strcpy(m1.filename, filename);
		m1.start_block = start;
		m2.magicnumber = previous_data.magicnumber;
		m2.no_of_files = previous_data.no_of_files + 1;
		m2.no_of_free_blocks = previous_data.no_of_free_blocks - m1.no_of_blocks;

		previous_data.no_of_files = m2.no_of_files;
		previous_data.no_of_free_blocks = m2.no_of_free_blocks;

		printf("\n no of files :%d free blocks:%d", m2.no_of_files, m2.no_of_free_blocks);
		printf("\nfilename:%s \tfilelength %d \tno_of_blocks %d \tstart address %d \t", m1.filename, m1.file_length, m1.no_of_blocks, m1.start_block);

		writemetadataintofile(diskname, &m1, &m2);
}
	else
	{

		while ((n = fread(buff, 1, BUFSIZE, file)) != 0) {
			writedatatofile(diskname, start + i+1, buff);
			i++;
			_itoa(start+i,temp,10);
			for (int k = 0; temp[k] != '\0'; k++){
				meta[metaindex++] = temp[k];
			}
			meta[metaindex++] = '\n';
			//fwrite(buff, 1, n, disk);
		}

		writedatatofile(diskname, start, meta);

		m1.file_length = ftell(file);
		m1.no_of_blocks = i+1;
		strcpy(m1.filename, filename);
		m1.start_block = start;
		m2.magicnumber = previous_data.magicnumber;
		m2.no_of_files = previous_data.no_of_files + 1;
		m2.no_of_free_blocks = previous_data.no_of_free_blocks - m1.no_of_blocks;

		previous_data.no_of_files = m2.no_of_files;
		previous_data.no_of_free_blocks = m2.no_of_free_blocks;

		printf("\n no of files :%d free blocks:%d", m2.no_of_files, m2.no_of_free_blocks);
		printf("\nfilename:%s \tfilelength %d \tno_of_blocks %d \tstart address %d \t", m1.filename, m1.file_length, m1.no_of_blocks, m1.start_block);

		writemetadataintofile(diskname, &m1, &m2);
	}
	fclose(file);
}

void write_from_disk(char *diskname, char *filename, char*destination){
	size_t n;
	struct meta m2;
	struct metadata m1;
	int count = 0;
	int metaindex = 0;
	char meta[size_of_block];
	int inistialblock = 0;
	void* buff = malloc(size_of_block);
	readdatafromdisk(diskname, 0, buff);
	memcpy(&m2, buff, sizeof(struct meta));
	int rt;

	//printf("\n no of files :%d free blocks:%d", m2.no_of_files, m2.no_of_free_blocks);
	for (int i = 0; i < m2.no_of_files; i++){
		
			memcpy(&m1, (char*)buff + metasize + (i)*metadatasize, sizeof(struct metadata));
			if (m1.file_length != 1){
			if (!strcmp(m1.filename, filename)){
				FILE *desti = fopen(destination, "wb");
				readdatafromdisk(diskname, m1.start_block, meta);
				
				while (meta[metaindex] != '\n')
					inistialblock = inistialblock * 10 + meta[metaindex++] - '0';
				metaindex++;
				int lenth_of_file = m1.file_length;
				do{
					//printf("===%d===%d\n", inistialblock,metaindex);
					readdatafromdisk(diskname, inistialblock, buff);
					if (lenth_of_file < size_of_block)
						rt = fwrite(buff, 1, lenth_of_file, desti);
					else
						fwrite(buff, 1, BUFSIZE, desti);
					lenth_of_file -= size_of_block;
					inistialblock = 0;
					while (meta[metaindex] != '\n')
						inistialblock = inistialblock * 10 + meta[metaindex++] - '0';
					metaindex++;
				} while (lenth_of_file > 0);
				fclose(desti);
			}

		}
		else
		{
			//memcpy(&m1, (char*)buff + metasize + (i)*metadatasize, sizeof(struct metadata));
			if (!strcmp(m1.filename, filename)){
				FILE *desti = fopen(destination, "wb");
				int inistialblock = m1.start_block;
				readdatafromdisk(diskname, inistialblock, meta);


				int lenth_of_file = m1.file_length;
				do{
					readdatafromdisk(diskname, inistialblock, buff);
					if (lenth_of_file < size_of_block)
						rt = fwrite(buff, 1, lenth_of_file, desti);
					else
						fwrite(buff, 1, BUFSIZE, desti);
					lenth_of_file -= size_of_block;
					inistialblock++;



				} while (lenth_of_file > 0);
				fclose(desti);
			}
		}
	}
}
void print_meta_data(char *diskname){
	printf("\n in meta data print\n");
	if (previous_data.no_of_files == 0){
		return;
	}
	struct meta m2;
	struct metadata m1;
	void* buff = malloc(size_of_block);
	readdatafromdisk(diskname, 0, buff);
	memcpy(&m2, buff, sizeof(struct meta));
	//fread(&m2, sizeof(struct meta), 1, disk);
	//printf("\n no of files :%d free blocks:%d", m2.no_of_files, m2.no_of_free_blocks);
	for (int i = 0; i < m2.no_of_files; i++){
		memcpy(&m1, (char*)buff + metasize + (i)*metadatasize, sizeof(struct metadata));
		//fseek(disk, metasize + (i)*metadatasize, SEEK_SET);
		//fread(&m1, sizeof(struct metadata), 1, disk);
		printf("\nfilename:%s \t length:%d \t startblock:%d \t no of blocks :%d", m1.filename, m1.file_length, m1.start_block, m1.no_of_blocks);
	}
	//fclose(disk);
}
void list_directories(char *diskname){
	if (previous_data.no_of_files == 0){
		return;
	}
	struct meta m2;
	struct metadata m1;
	void* buff = malloc(size_of_block);
	readdatafromdisk(diskname, 0, buff);
	memcpy(&m2, buff, sizeof(struct meta));
	//fread(&m2, sizeof(struct meta), 1, disk);
	//printf("\n no of files :%d free blocks:%d", m2.no_of_files, m2.no_of_free_blocks);
	for (int i = 0; i < m2.no_of_files; i++){
		memcpy(&m1, (char*)buff + metasize + (i)*metadatasize, sizeof(struct metadata));
		//fseek(disk, metasize + (i)*metadatasize, SEEK_SET);
		//fread(&m1, sizeof(struct metadata), 1, disk);
		printf("\nfilename:%s", m1.filename);
	}
	//fclose(disk);
}



void format(char *diskname){

	return;
}


int main(){

	char diskname[50] = "disk.hdd";
	char str[100], src[100], des[100];
	struct meta m2;
	void* buff = malloc(size_of_block);
	readdatafromdisk(diskname, 0, buff);
	memcpy(&m2, buff, sizeof(struct meta));

	if (m2.magicnumber == 0x444E524D)
	{
		previous_data.magicnumber = 0x444E524D;
		previous_data.no_of_files = m2.no_of_files;
		previous_data.no_of_free_blocks = m2.no_of_free_blocks;
	}
	else{
		previous_data.magicnumber = 0x444E524D;
		previous_data.no_of_files = 0;
		previous_data.no_of_free_blocks = 6399;
	}

	printf("\n>>>");
	while (scanf_s("%s", str, 50) != EOF){
		switch (str[0]){
		case 'M':
			if (!(strcmp(str, "METADATA")))
			{
				print_meta_data(diskname);
			}
			break;
		case 'C':
			if (!(strcmp(str, "COPY_INTO_DISK")))
			{
				scanf_s("%s", src, 50);
				write_into_disk(diskname, src);
			}
			else if (!(strcmp(str, "COPY_FROM_DISK"))){
				scanf_s("%s", src, 50);
				scanf_s("%s", des, 50);
				write_from_disk(diskname, src, des);
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
		case 'F':
			if (!(strcmp(str, "FORMAT")))
			{
				format(diskname);
			}
			else
				printf("\nentered a invalid command format");
			break;
		default:
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
