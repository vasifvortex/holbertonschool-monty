#include "monty.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char **token_arr = NULL;
int status = 0;

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
		status = 1;
	}
	monty = fopen(argv[1], "r");
	if (monty == NULL)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s", argv[1]);
		status = 1;
	}
	while (fgets(buf, 1024, monty) != NULL && status == 0)
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
		if (instructions[i].opcode == NULL)
		{
			dprintf(STDERR_FILENO, "L%d: unknown instruction %s", line_number, token_arr[0]);
			status = 1;
		}
		i = 0;
		free(token_arr);
		line_number++;
	}
	fclose(monty);
	free_stack(stack);
	if (status == 1)
		exit(EXIT_FAILURE);
	return (0);
}
