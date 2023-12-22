#include "main.h"

/**
* main - entry point to the pogram
*@argc: arguments counter
*@argv: arguments vector.
*
*Return:Returns condition.
*/
int main(__attribute__((unused)) int argc, char **argv)
{
	char *input, **cmd;
	int cmd_count = 1, status = 0;

	while (1)
	{
		if(isatty(STDIN_FILENO))
			printf("$ ");
		input = _getline();

		if (check_cmd(input) != 0)
		{
			free(input);
			continue;
		}
		cmd = tok_cmd(input);
		free(input);

		status = exe_cmd(cmd, cmd_count, argv);
		free_double_pointer(cmd);

		cmd_count++;
	}
	return (status);
}
