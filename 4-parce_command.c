#include "main.h"

/**
 * tok_cmd - Parses the command recieved from stdin
 * @input: String gathered from stdin
 * Return: Parsed strings to be used as tokens
 */
char **tok_cmd(char *input)
{
	char **tokens;
	char *string;
	int i;

	if (input == NULL)
		return (NULL);
	tokens = malloc(sizeof(char *) * 512);
	if (!tokens)
	{
		perror("allocation error");
		return (NULL);
	}
	string = strtok(input, DELIME);
	for (i = 0; string; i++)
	{
		tokens[i] = strdup(string);
		string = strtok(NULL, DELIME);
	}
	tokens[i] = NULL;
	return (tokens);
}
