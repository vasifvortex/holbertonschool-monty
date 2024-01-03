#include "monty.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
/**
 * delim_counter - counts deliminators in the str.
 * @str: string.
 * @delim: deliminators.
 * Return: deliminator count.
 */
int delim_counter(char *str, char *delim)
{
	int j = 0, i = 1, count = 0;

	while (str[i] != '\0')
	{
		while (delim[j] != '\0')
		{
			if ((str[i - 1] == delim[j]) && str[i] > 32)
			{
				count++;
				break;
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (count);
}
/**
 * token_parse - splits a string.
 * @str: string.
 * @delim: deliminators.
 * Return: pointer to the array of divided strings.
 */
char **token_parse(char *str, char *delim)
{
	int delim_count, token_number = 0;
	char **strarr = NULL;
	char *token = NULL;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	delim_count = delim_counter(str, delim);
	/*2 places for last token and NULL ending*/
	strarr = malloc((delim_count + 2) * sizeof(char *));
	if (strarr == NULL)
	{
		dprintf(STDERR_FILENO, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(str, delim);
	while (token != NULL)
	{
		strarr[token_number] = token;
		token = strtok(NULL, delim);
		token_number++;
	}
	strarr[token_number] = NULL;
	return (strarr);
}
