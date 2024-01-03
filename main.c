#include "monty.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char **token_arr = NULL;

int main(int argc, char *argv[])
{
	stack_t *stack = NULL;
	instruction_t instructions[] = {{"push", push}, {"pall", pall}, {NULL, NULL}};
	FILE *monty;
	char buf[1024];
	int line_number = 1, i = 0;

	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		exit(EXIT_FAILURE); }
	monty = fopen(argv[1], "r");
	while (fgets(buf, 1024, monty) != NULL)
	{
		token_arr = token_parse(buf, " $\n\t");
		while (instructions[i].opcode != NULL)
		{
			if (token_arr[0] == NULL || token_arr[0][0] == '\0')
				break;
			if (strcmp(token_arr[0], instructions[i].opcode) == 0)
			{
				instructions[i].f(&stack, line_number);
				break;
			}
			i++;
		}
		i = 0;
		free(token_arr);
		line_number++;
	}
	fclose(monty);
	return (0);
}
