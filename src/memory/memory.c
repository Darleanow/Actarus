#include "memory.h"

void	*memset(void *pointer, int c, size_t size)
{
	char	*c_pointer;
	int		i;

	*c_pointer = (char *) pointer;
	i = 0;
	while (i < size)
	{
		c_pointer[i] = (char) c;
		i++;
	}
	return (pointer);
}
