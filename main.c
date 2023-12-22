#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROMPT "#cisfun$ "
#define MAX_CMD_LEN 1024

/**
 * main - Entry point for the simple shell.
 *
 * Return: EXIT_SUCCESS on success, or an error code on failure.
 */
int main(void)
{
    char command[MAX_CMD_LEN];
    char *argv[2];
    pid_t pid;
    int status;

    while (1)
    {
        printf(PROMPT); /* Display prompt */
        fflush(stdout);

        if (!fgets(command, MAX_CMD_LEN, stdin)) /* Read command from stdin */
        {
            if (feof(stdin)) /* Check for end-of-file (Ctrl+D) */
            {
                printf("\n");
                return EXIT_SUCCESS;
            }
            perror("fgets");
            return EXIT_FAILURE;
        }

        if (command[strlen(command) - 1] == '\n')
            command[strlen(command) - 1] = '\0'; /* Remove newline at end */

        argv[0] = command; /* Prepare arguments for execvp */
        argv[1] = NULL;

        pid = fork(); /* Fork a new process */
        if (pid == -1)
        {
            perror("fork");
            return EXIT_FAILURE;
        }
        if (pid == 0)
        {
            /* Child process */
            if (execvp(command, argv) == -1)
            {
                perror(command); /* Print error if exec fails */
                return EXIT_FAILURE;
            }
            exit(EXIT_SUCCESS);
        }
        else
        {
            /* Parent process */
            wait(&status); /* Wait for child process to finish */
        }
    }

    return EXIT_SUCCESS;
}
