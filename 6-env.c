#include "main.h"
/**
 * _env - print env
*/
void _env(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}
