#include "main.h"
/**
 * free_double_pointer - free double pointer
 * @ptr: pointer to free it
*/
void free_double_pointer(char **ptr)
{
	int i;

	for (i = 0; ptr[i] != NULL; i++)
	{
		free(ptr[i]);
	}
	free(ptr);
}
