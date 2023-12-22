#include "main.h"
/**
 * check_cmd - check if input is '\n' or 'exit'
 * @input: sting to check it
 * Return: check ok 0
*/
int check_cmd(char *input)
{
	if (input[0] == '\n')
		return (1);

	if (strcmp(input, "exit\n") == 0)
	{
		free(input);
		exit(2);
	}
	if (strcmp(input, "env\n") == 0)
	{
		_env();
		return (3);
	}

	return (0);
}
