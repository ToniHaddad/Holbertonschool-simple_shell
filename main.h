#ifndef HEADERFILE
#define HEADERFILE

#define DELIME " \t\r\n\a"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>


extern char **environ;

char *_getline(void);
char **tok_cmd(char *input);
int exe_cmd(char **cmd, int c, char **argv);
int path_cmd(char **cmd);
char *build(char *token, char *value);
int check_cmd(char *input);
void _env(void);
void free_double_pointer(char **pointer);

#endif
