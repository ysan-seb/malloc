#include "malloc.h"

static size_t		align(size_t size)
{
	return ((size % 16 != 0) ? size += 16 - (size % 16) : size);
}

void		*malloc(size_t size)
{

    debug = 0;

	size = align(size);
	// ft_putnbr(size);
	// ft_putchar('\n');
	if (size == 0)
		return (malloc(16));
	if (size < TINY)
        	return (malloc_tiny(size));
	else if (size > TINY && size < SMALL)
        	return (malloc_small(size));
	else
		return (malloc_large(size));
}