// day7-compilers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include "tokenizer.h"
#include "mapopcode.h"
#include "stack.h"


static int address = 0;
static int tableindex = 0;
static int interindex = 0;
static int labelindex = 0;


struct  SymbolTable
{
	char name;
	int address;
	int size;
};

struct Label{
	char blockname[10];
	int address;
};

struct Intermediate{
	int sno;
	int opcode;
	int parameters[4];
};


struct Intermediate intermediatetable[100];
struct Label label[50];
struct SymbolTable table[100];

int getopcodefromsymboltable(char str){
	for (int i = 0; i < tableindex; i++){
		if (table[i].name == str){
			return table[i].address;
		}
	}
	return -1;
}
int labelcode(char*str){
	for (int i = 0; i < labelindex; i++)
		if (strcmp(label[i].blockname, str) == 0)
			return label[i].address;
	return -1;
}
void writetooutput(){
	FILE *fp = fopen("output.txt", "wb");

	fwrite(&interindex, 1, sizeof(int), fp);
	for (int i = 0; i < interindex; i++)
		fwrite(&intermediatetable[i], 1, sizeof(struct Intermediate), fp);
	fwrite(&tableindex, 1, sizeof(int), fp);
	for (int i = 0; i < tableindex; i++)
		fwrite(&table[i], 1, sizeof(struct SymbolTable), fp);
	fwrite(&labelindex, 1, sizeof(int), fp);
	for (int i = 0; i < labelindex; i++)
		fwrite(&label[i], 1, sizeof(struct Label), fp);

	fclose(fp);
}

void parseinput(int *stack, int *top){
	char ch;
	char **str = (char**)malloc(100 * 100);
	char getline[100];
	int lineindex = 0;
	FILE *input = fopen("input.txt", "r");


	while ((ch = fgetc(input)) != EOF){

		lineindex = 0;
		while (ch != '\n'){
			getline[lineindex++] = ch;
			if ((ch = fgetc(input)) == EOF)
				break;
		}
		getline[lineindex++] = '\0';
		str = tokenize(getline, &lineindex);
		if (str[0][0] != 'E'&&str[1][0] == ':'){
			strcpy(label[labelindex].blockname, str[0]);
			label[labelindex].address = interindex;
			labelindex++;
		}
		if (!(strcmp(str[0], "DATA")))
		{
			table[tableindex].address = address;
			table[tableindex].name = str[1][0];
			if (strlen(getline)>7 && str[2][0] == '['){
				table[tableindex].size = str[3][0] - '0';
				address += table[tableindex].size;
			}
			else{
				table[tableindex].size = 1;
				address++;
			}
			tableindex++;
		}
		else if (!(strcmp(str[0], "CONST"))){
			table[tableindex].address = address;
			table[tableindex].name = str[1][0];
			//write data into memory
			table[tableindex].size = str[3][0] - '0';
			tableindex++;
		}
		else if (!(strcmp(str[0], "READ"))){
			intermediatetable[interindex].opcode = getopcode(str[0]);
			intermediatetable[interindex].sno = interindex;
			intermediatetable[interindex].parameters[0] = getopcode(str[1]);
			interindex++;
		}
		else if (!(strcmp(str[0], "MOV")) || !(strcmp(str[0], "MOV"))){

			if ((strlen(str[3]) == 2) || str[2][0] == '['){
				intermediatetable[interindex].opcode = getopcode("MOVR");
				intermediatetable[interindex].sno = interindex;
				if (str[2][0] != '['){
					intermediatetable[interindex].parameters[0] = getopcodefromsymboltable(str[1][0]);
					intermediatetable[interindex].parameters[1] = getopcode(str[3]);
				}
				else{
					intermediatetable[interindex].parameters[0] = getopcodefromsymboltable(str[1][0]) + (str[3][0] - '0');
					intermediatetable[interindex].parameters[1] = getopcode(str[6]);
				}
				interindex++;
			}
			else{
				intermediatetable[interindex].opcode = getopcode("MOVM");
				intermediatetable[interindex].sno = interindex;
				intermediatetable[interindex].parameters[0] = getopcode(str[1]);
				intermediatetable[interindex].parameters[1] = getopcodefromsymboltable(str[3][0]);
				interindex++;
			}
		}
		else if (!(strcmp(str[0], "ADD"))){
			intermediatetable[interindex].opcode = getopcode(str[0]);
			intermediatetable[interindex].sno = interindex;
			intermediatetable[interindex].parameters[0] = getopcode(str[1]);
			intermediatetable[interindex].parameters[1] = getopcode(str[3]);
			intermediatetable[interindex].parameters[2] = getopcode(str[5]);
			interindex++;
		}
		else if (!(strcmp(str[0], "SUB"))){
			intermediatetable[interindex].opcode = getopcode(str[0]);
			intermediatetable[interindex].sno = interindex;
			intermediatetable[interindex].parameters[0] = getopcode(str[1]);
			intermediatetable[interindex].parameters[1] = getopcode(str[3]);
			intermediatetable[interindex].parameters[2] = getopcode(str[5]);
			interindex++;
		}
		else if (!(strcmp(str[0], "MUL"))){
			intermediatetable[interindex].opcode = getopcode(str[0]);
			intermediatetable[interindex].sno = interindex;
			intermediatetable[interindex].parameters[0] = getopcode(str[1]);
			intermediatetable[interindex].parameters[1] = getopcode(str[3]);
			intermediatetable[interindex].parameters[2] = getopcode(str[5]);
			interindex++;
		}
		else if (!(strcmp(str[0], "PRINT"))){
			intermediatetable[interindex].opcode = getopcode(str[0]);
			intermediatetable[interindex].sno = interindex;
			if (strlen(str[1]) == 1)
				intermediatetable[interindex].parameters[0] = getopcodefromsymboltable(str[1][0]);
			else
				intermediatetable[interindex].parameters[0] = getopcode(str[1]);
			interindex++;
		}
		else if (!(strcmp(str[0], "IF"))){
			push(stack, top, interindex);
			intermediatetable[interindex].opcode = getopcode(str[0]);
			intermediatetable[interindex].sno = interindex;
			intermediatetable[interindex].parameters[0] = getopcode(str[1]);
			intermediatetable[interindex].parameters[2] = getopcode(str[2]);
			intermediatetable[interindex].parameters[1] = getopcode(str[3]);
			interindex++;
		}
		else if (!(strcmp(str[0], "ELSE"))){
			push(stack, top, interindex);
			intermediatetable[interindex].opcode = getopcode("JMP");
			intermediatetable[interindex].sno = interindex;
			interindex++;
		}
		else if (!(strcmp(str[0], "ENDIF"))){
			int index = pop(stack, top), temp = interindex;
			while (intermediatetable[index].opcode != getopcode("IF")){
				intermediatetable[index].parameters[0] = temp;
				temp = index + 1;
				index = pop(stack, top);
			}
			intermediatetable[index].parameters[3] = temp;
			temp = index + 1;
			index = pop(stack, top);

		}
		else if (!(strcmp(str[0], "JUMP"))){
			intermediatetable[interindex].opcode = getopcode("JMP");
			intermediatetable[interindex].sno = interindex;
			intermediatetable[interindex].parameters[0] = labelcode(str[1]);
			interindex++;

		}
		else if (!(strcmp(str[0], "END"))){
			writetooutput();

		}
		else{
			printf("%s not in list", getline);
		}

	}


	fclose(input);
}

int parse(){
	int stack[50], top = -1;

	parseinput(stack, &top);
	printf("\n======intermediate code=====\n");
	for (int i = 0; i < interindex; i++)
		printf("\n %d\t %d\t %d\t %d\t %d\t %d\t ", intermediatetable[i].sno, intermediatetable[i].opcode, intermediatetable[i].parameters[0], intermediatetable[i].parameters[1], intermediatetable[i].parameters[2], intermediatetable[i].parameters[3]);
	printf("\n\n===========symbol table=======\n");
	for (int i = 0; i < tableindex; i++)
		printf("\n%c\t %d\t %d\t", table[i].name, table[i].address, table[i].size);

	getchar();
	return 0;
}