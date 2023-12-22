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
        fflush(stdout); // Ensure the prompt is displayed immediately

        characters = getline(&buffer, &bufsize, stdin); // Read input
        if (characters == -1)
        {
            free(buffer);
            if (feof(stdin))
            { // Handle EOF (Ctrl+D)
                printf("\n");
                exit(EXIT_SUCCESS);
            }
            else
            {
                perror("getline");
                exit(EXIT_FAILURE);
            }
        }

        // Remove the newline character at the end of the input
        buffer[strcspn(buffer, "\n")] = 0;

        // Check for the exit command
        if (strcmp(buffer, "exit") == 0)
        {
            free(buffer);
            exit(EXIT_SUCCESS);
        }

        pid = fork(); // Create a new process
        if (pid == -1)
        {
            perror("Error:");
            continue;
        }

        if (pid == 0)
        {
            // Child process
            char *argv[] = {buffer, NULL};
            if (execve(buffer, argv, NULL) == -1)
            {
                perror(buffer);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            // Parent process
            wait(&status); // Wait for the child process to finish
        }
    }

    free(buffer);
    return 0;
}