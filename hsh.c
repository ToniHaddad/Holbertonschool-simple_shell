#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PROMPT "#cisfun$ "
#define BUFFER_SIZE 1024

int main(void)
{
    char *buffer = NULL;
    size_t bufsize = BUFFER_SIZE;
    ssize_t characters;
    pid_t pid;
    int status;

    while (1)
    {
        printf(PROMPT);
        fflush(stdout);

        characters = getline(&buffer, &bufsize, stdin);
        if (characters == -1)
        {
            free(buffer);
            if (feof(stdin))
            {
                printf("\n");
                exit(EXIT_SUCCESS);
            }
            else
            {
                perror("getline");
                exit(EXIT_FAILURE);
            }
        }

        buffer[strcspn(buffer, "\n")] = 0;

        pid = fork();
        if (pid == 0)
        {
            // Child process
            if (execve(buffer, NULL, NULL) == -1)
            {
                perror(buffer);
                exit(EXIT_FAILURE);
            }
        }
        else if (pid < 0)
        {
            // Error forking
            perror("fork");
        }
        else
        {
            // Parent process
            waitpid(pid, &status, 0);
        }
    }

    free(buffer);
    return 0;
}
