#include "malloc.h"

 void 	*valloc(size_t size)
 {
	 write(1, "VALLOC\n", 7);
	 return (NULL);
 }

void	*calloc(size_t count, size_t size) {
	int i;
	void *ptr;

	i = 0;
	if (!count || !size)
	{
		ptr = malloc(16);
		memset(ptr, 0, 16);
	}
	else
	{
		ptr = malloc(count * size);
		memset(ptr, 0, size);
	}
	return (ptr);

}

void    *realloc(void *ptr, size_t size)
{
	t_zone *data;
	void	*new_zone;

    (debug) ? ft_putstr("\e[1;38;5;6m") : 0;
	(debug) ? write(1, "REALLOC  ", 8) : 0;
	(debug) ? ft_putnbr(size) : 0;
    (debug) ? ft_putstr("\e[0m") : 0;
	(debug) ? ft_putptr(ptr) : 0;
	(debug) ? ft_putchar('\n') : 0;
	// if (size == 0)
	// 	return (realloc(ptr, 16));
	if (!ptr)
		return (malloc(size));
	else if (ptr && size == 0)
		free(ptr);
	else if (!(data = get_ptr(ptr)))
		return (NULL);
	else
	{
		if (!(new_zone = malloc(size)))
			return (NULL);
		memcpy(new_zone, ptr, data->size);
		free(ptr);
		return (new_zone);
	}
	return (NULL);
}

