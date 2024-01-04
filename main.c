#include "monty.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
/**
 * main - Entry point.
 * @argc: argument count.
 * @argv: arguments.
 * Return: 0 or 1 based on success.
 */
int main(int argc, char *argv[])
{
	stack_t *stack = NULL;
	FILE *monty;
	char buf[1024];
	int line_number = 1;

	globals.status = 0;
	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	monty = fopen(argv[1], "r");
	if (monty == NULL)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while (fgets(buf, 1024, monty) != NULL && globals.status == 0)
	{
		globals.token_arr = token_parse(buf, " $\n\t");
		execution(&stack, line_number);
		free(globals.token_arr);
		line_number++;
	}
	fclose(monty);
	free_stack(stack);
	if (globals.status == 1)
		exit(EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
