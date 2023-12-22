#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROMPT "#cisfun$ "
#define MAX_CMD_LEN 1024

int main(void)
{
    char command[MAX_CMD_LEN];
    char *argv[2];
    pid_t pid;
    int status;
    int is_interactive = isatty(STDIN_FILENO);

    while (1)
    {
        if (is_interactive)
        {
            printf(PROMPT); /* Display prompt only in interactive mode */
        }
        fflush(stdout);

        if (!fgets(command, MAX_CMD_LEN, stdin))
        {
            if (feof(stdin)) /* Check for end-of-file (Ctrl+D) */
            {
                printf("");
                return EXIT_SUCCESS;
            }
            perror("fgets");
            return EXIT_FAILURE;
        }

        if (command[strlen(command) - 1] == '\n')
            command[strlen(command) - 1] = '\0'; /* Remove newline at end */

        argv[0] = command;
        argv[1] = NULL;

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            return EXIT_FAILURE;
        }
        if (pid == 0)
        {
            if (execvp(command, argv) == -1)
            {
                perror(command);
                return EXIT_FAILURE;
            }
            exit(EXIT_SUCCESS);
        }
        else
        {
            wait(&status);
        }
    }
    return EXIT_SUCCESS;
}
