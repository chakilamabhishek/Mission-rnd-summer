#include <stdlib.h>
#include <string.h>

char *strcpyWithBounds(char *string, int l, int u) {
	char *res = (char *)malloc(sizeof(char) * (u - l + 2));
	int i;
	for (i = l; i <= u; i++) {
		res[i - l] = string[i];
	}
	res[i - l] = '\0';
	return res;
}

char **tokenize(char *commandString, int *command_length) {
	int k = 0;
	char **command = (char **)malloc(sizeof(char *) * 100);
	int id_start_index = 0;
	int identifier_scanner = -1;
	int i;
	for (i = 0; commandString[i] != '\0'; i++) {
		if ((commandString[i] >= 'A' && commandString[i] <= 'Z')
			|| (commandString[i] >= 'a' && commandString[i] <= 'z')
			|| (commandString[i] >= '0' && commandString[i] <= '9')
			|| (commandString[i] == '.')
			|| (commandString[i] == '_')) {
			if (identifier_scanner != 1 && identifier_scanner != -1) {
				command[k++] = strcpyWithBounds(commandString, id_start_index, i - 1);
				id_start_index = i;
			}
			identifier_scanner = 1;
		}
		else if (commandString[i] == ' ' ||
			commandString[i] == '\t' ||
			commandString[i] == '\n') {
			if (identifier_scanner != -1) {
				command[k++] = strcpyWithBounds(commandString, id_start_index, i - 1);
			}
			identifier_scanner = -1;
			id_start_index = i + 1;
		}
		else if (commandString[i] == ')'
			|| commandString[i] == '('
			|| commandString[i] == '['
			|| commandString[i] == ']' || commandString[i] == ',' || commandString[i] == ':') {
			if (identifier_scanner != -1)
				command[k++] = strcpyWithBounds(commandString, id_start_index, i - 1);
			command[k++] = strcpyWithBounds(commandString, i, i);
			identifier_scanner = -1;
			id_start_index = i + 1;
		}
		else {
			if (identifier_scanner != 0 && identifier_scanner != -1) {
				command[k++] = strcpyWithBounds(commandString, id_start_index, i - 1);
				id_start_index = i;
			}
			identifier_scanner = 0;
		}
	}
	if (id_start_index != i) {
		command[k++] = strcpyWithBounds(commandString, id_start_index, i - 1);
	}
	*command_length = k;
	return command;
}

char *deTokenize(char **tokens, int tokensLen) {
	char *res = (char *)malloc(sizeof(char) * 1000);
	res[0] = '\0';
	for (int i = 0; i < tokensLen; i++) {
		strcat(res, tokens[i]);
		strcat(res, " ");
	}
	return res;
}



