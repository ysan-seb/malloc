#include "malloc.h"

size_t	align(size_t size)
{
	return ((size % 16 != 0) ? size += 16 - (size % 16) : size);
}