#include<stdio.h>
char diskname[20];
static int size_of_block, BUFSIZE;


long init(char *dname ,int size){
	FILE *disk = fopen(dname, "rb");
	strcpy(diskname,dname);
	fseek(disk, 0, SEEK_END);
	long totalsize = ftell(disk);
	size_of_block = BUFSIZE = size;
	return totalsize / size;
}


int readdatafromdisk( int blocknumber, void *buff){
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


void writedatatofile(int blocknumber, void *buff){
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