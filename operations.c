#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int check_and_convert_int(char *str, unsigned int line_number)
{
	int i = 0, flag = 0;

	while (str && str[i] != '\0')
	{
		if(str[i] >= '0' && str[i] <= '9')
			flag = 1;
		else
		{
			flag = 0;
			break;
		}
		i++;
	}
	if (flag == 0)
	{
		dprintf(STDERR_FILENO, "L%u: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	return (atoi(str));
}
void push(stack_t **stack, unsigned int line_number)
{
	int num = check_and_convert_int(token_arr[1], line_number); /* global variable */
	stack_t *new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		dprintf(STDERR_FILENO, "Error: malloc failed\n");
		exit(EXIT_FAILURE); }
	new_node->n = num;
	new_node->prev = NULL;
	new_node->next = *stack;
	if (*stack != NULL)
		(*stack)->prev = new_node;
	*stack = new_node;
}

void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;
	while (temp != NULL)
	{
		printf("%d\n", temp->n);
		temp = temp->next;
	}
}