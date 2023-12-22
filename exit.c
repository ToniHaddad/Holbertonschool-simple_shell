#include "shell.h"

/**
 * Placeholder Comment
 */
char *custom_strncpy(char *destination, char *source, int num_chars)
{
	int index_dest = 0, index_src = 0;
	char *start = destination;

	while (source[index_src] != '\0' && index_src < num_chars - 1)
	{
		destination[index_dest] = source[index_src];
		index_dest++;
		index_src++;
	}
	if (index_src < num_chars)
	{
		int j = index_src;
		while (j < num_chars)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (start);
}

/**
 * Placeholder comment
 */
char *customStrncat(char *destination, char *source, int max_bytes)
{
	int dest_index = 0, src_index = 0;
	char *result = destination;

	while (destination[dest_index] != '\0')
		dest_index++;

	while (source[src_index] != '\0' && src_index < max_bytes)
	{
		destination[dest_index] = source[src_index];
		dest_index++;
		src_index++;
	}

	if (src_index < max_bytes)
		destination[dest_index] = '\0';

	return (result);
}

/**
 * Placeholder comment
 */
char *customStrchr(char *str, char ch)
{
	do {
		if (*str == ch)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
