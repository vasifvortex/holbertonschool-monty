#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/**
 * swap - swaps top 2 element of stack.
 * @stack: stack.
 * @line_number: line number in the file.
 */
void swap(stack_t **stack, unsigned int line_number)
{
	int n, ln = line_number;
	stack_t *next;

	if (stack && *stack && (*stack)->next)
	{
		next = (*stack)->next;
		n = (*stack)->n;
		(*stack)->n = next->n;
		next->n = n;
		return;
	}
	dprintf(STDERR_FILENO, "L%u: can't swap, stack too short\n", ln);
	globals.status = 1;
}
/**
 * free_stack - frees stack.
 * @stack: stack.
 */
void free_stack(stack_t *stack)
{
	stack_t *temp = NULL;

	while (stack)
	{
		temp = stack->next;
		free(stack);
		stack = temp;
	}
}
