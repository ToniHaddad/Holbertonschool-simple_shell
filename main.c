#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define PROMPT "#cisfun$ "

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char *argv[2];
    int status;
    pid_t child_pid;

    while (1)
    {
        printf(PROMPT);

        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            free(line);
            /*
             * Handle EOF (Ctrl+D) and errors in reading the line
             */
            if (feof(stdin))
                break; /* EOF encountered */
            else
                continue; /* Error encountered */
        }

        line[nread - 1] = '\0'; /* Remove newline character */
        argv[0] = line;         /* Command */
        argv[1] = NULL;         /* Null-terminate the argument list */

        child_pid = fork();
        if (child_pid == 0)
        {
            /* Child process */
            if (execve(argv[0], argv, NULL) == -1)
            {
                perror(argv[0]);
                exit(EXIT_FAILURE);
            }
        }
        else if (child_pid > 0)
        {
            /* Parent process */
            wait(&status);
        }
        else
        {
            /* Fork failed */
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}
