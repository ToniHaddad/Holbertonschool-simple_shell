#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

#define PROMPT "#cisfun$ "
#define MAX_CMD_LEN 1024

/* Function to trim leading and trailing spaces */
char *trim_whitespace(char *str)
{
    char *end;

    /* Trim leading space */
    while (isspace((unsigned char)*str))
        str++;

    if (*str == 0) /* All spaces? */
        return str;

    /* Trim trailing space */
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    /* Write new null terminator character */
    end[1] = '\0';

    return str;
}

int main(void)
{
    char command[MAX_CMD_LEN];
    char *argv[2];
    char *trimmed_command;
    pid_t pid;
    int status;
    int is_interactive = isatty(STDIN_FILENO);

    while (1)
    {
        if (is_interactive)
        {
            printf(PROMPT);
        }
        fflush(stdout);

        if (!fgets(command, MAX_CMD_LEN, stdin))
        {
            if (feof(stdin)) /* Check for end-of-file (Ctrl+D) */
            {
                printf("\n");
                return EXIT_SUCCESS;
            }
            perror("fgets");
            return EXIT_FAILURE;
        }

        trimmed_command = trim_whitespace(command);
        if (strlen(trimmed_command) == 0) /* Skip empty commands */
            continue;

        argv[0] = trimmed_command;
        argv[1] = NULL;

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            return EXIT_FAILURE;
        }
        if (pid == 0)
        {
            if (execvp(trimmed_command, argv) == -1)
            {
                perror(trimmed_command);
                exit(EXIT_FAILURE);
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
