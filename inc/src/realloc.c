#include "malloc.h"

int     need_space(size_t size1, size_t size2)
{
    size_t origin;
    size_t asked;
    
	origin = (size1 - 1 + sizeof(t_zone)) / getpagesize() + 1;
    asked = (size2 - 1 + sizeof(t_zone)) / getpagesize() + 1;
    if (origin == asked || origin > asked)
        return (0);
    else
        return (1);
}

static int	check_pointer(void *ptr)
{
	t_zone *zone;

	zone = g_zone;
	if (!zone)
		return (0);
	else
	{
		while (zone)
		{
			if (zone->ptr == ptr)
				return (1);
			zone = zone->next;
		}
	}
	return (0);
}
// void	*calloc(size_t count, size_t size) {
// 	int i;
// 	void *ptr;

// 	i = 0;
// 	write(1, "CALLOC -> ", 10);
// 	if (!count || !size)
// 	{
// 		ptr = malloc(16);
// 		memset(ptr, 0, 16);
// 	}
// 	else
// 	{
// 		ptr = malloc(count * size);
// 		memset(ptr, 0, size);
// 	}
// 	return (ptr);

// }

void    *realloc(void *ptr, size_t size)
{
	void	*new_zone;

	write(1, "REALLOC : ", 10);
	ft_putptr(ptr);
	if (size == 0)
		return (realloc(ptr, 16));
	if (!ptr && size > 0)
	{
		write(1, " -> ", 4);
		return (malloc(size));
	}
	if (!check_pointer(ptr))
	{
		write(1, " UNKNOWN\n", 9);
		return (NULL);
	}
	else
	{
		write(1, "PTR PTR\n", 8);
		if (!(new_zone = malloc(size)))
			return (NULL);
		memcpy(new_zone, ptr, size);
		free(ptr);
		return (new_zone);
	}
	write(1, " DONE\n", 6);
	return (NULL);
}