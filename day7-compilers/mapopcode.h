#include<string.h>

struct entry {
	char *str;
	int n;
};

struct entry dict[] = {
	"MOVR", 1,
	"MOVM", 2,
	"ADD", 3,
	"SUB", 4,
	"MUL", 5,
	"JMP", 6,
	"IF", 7,
	"EQ", 8,
	"LT", 9,
	"GT", 10,
	"LTEQ", 11,
	"GTEQ", 12,
	"PRINT", 13,
	"READ", 14,
	"AX", 0,
	"BX", 1,
	"CX", 2,
	"DX", 3,
	"EX", 4,
	"FX", 5,
	"GX", 6,
	"HX", 7,
	0, 0
};

int getopcode(char *key)
{
	int i = 0;
	char *name = dict[i].str;
	while (name) {
		if (strcmp(name, key) == 0)
			return dict[i].n;
		name = dict[++i].str;
	}
	return -1;
}