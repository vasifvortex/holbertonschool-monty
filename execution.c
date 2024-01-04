#include "monty.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
/**
 * execution - executes instructions.
 * @stack: stack.
 * @line_number: line number in file.
 */
void execution(stack_t **stack, int line_number)
{
	int i = 0;
	instruction_t instructions[] = {{"push", push}, {"pall", pall}, {NULL, NULL}};
	char **t_a = globals.token_arr;

	while (instructions[i].opcode != NULL)
	{
		if (t_a[0] == NULL || t_a[0][0] == '\0')
			break;
		if (strcmp(t_a[0], instructions[i].opcode) == 0)
		{
			instructions[i].f(stack, line_number);
			break;
		}
		i++;
	}
	if (instructions[i].opcode == NULL)
	{
		dprintf(STDERR_FILENO, "L%d: unknown instruction %s\n", line_number, t_a[0]);
		globals.status = 1;
	}
}
