#include "main.h"

/**
 * exe_cmd - Excutes commands found in predefined path
 * @cmd: Array of parsed command strings
 * @c:Shell Excution Time Case of Command Not Found
 * @argv: Arguments before program starts(argv[0] == Shell Program Name)
 * Return: 1 Case Command Null -1 Wrong Command 0 Command Excuted
 */
int exe_cmd(char **cmd, int c, char **argv)
{
	pid_t pid;

	if (cmd[0] == NULL)
		return (1);

	pid = fork();
	if (pid == -1)
	{
		perror("Error fork");
		return (-1);
	}
	if (pid == 0)
	{
		if (strncmp(cmd[0], "/", 1) != 0)
			path_cmd(cmd);
		if (access(cmd[0], X_OK) != 0)
		{
			printf("%s: %d: %s: not found\n", argv[0], c, cmd[0]);
			free_double_pointer(cmd);
			exit(127);
		}
		if (execve(cmd[0], cmd, environ) == -1)
			return (2);
		else
			return (0);
	}
	wait(NULL);


	return (127);
}
