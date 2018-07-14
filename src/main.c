#include "malloc.h"

int		main(void) {

	void *ptr = 0;
	size_t size = 0;
	void *ret;

	ret = malloc(size);
	ret = realloc(ptr, size);
	free(ptr);
	show_alloc_mem(ptr);
	return (0);
}
