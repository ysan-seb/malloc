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

void	*calloc(size_t count, size_t size) {
	int i;
	void *ptr;

	i = 0;
	// write(1, "CALLOC -> ", 10);
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

void copy_block(t_zone *src , t_zone *dst)
{
	unsigned char *sdata ,* ddata;
	size_t i;

	i = 0;
	sdata = src->ptr;
	ddata = dst->ptr;
	// for (i=0; i*4<src->size && i*4<dst->size; i++)
	// 	ddata[i] = sdata[i];
	while(i * 4 < src->size && i * 4 < dst->size)
	{
		ddata[i] = sdata[i];
		i++;
	}
}


void    *realloc(void *ptr, size_t size)
{
	t_zone *data;
	void	*new_zone;

	// write(1, "REALLOC : ", 10);
	// ft_putptr(ptr);
	if (size == 0)
		return (realloc(ptr, 16));
	if (!ptr && size > 0)
	{
		// write(1, " -> ", 4);
		return (malloc(size));
	}
	if (!check_pointer(ptr))
	{
		write(1, " UNKNOWN\n", 9);
		return (NULL);
	}
	else
	{
		// write(1, " -> ", 4);
		if (!(new_zone = malloc(size)))
			return (NULL);
			
		if (!(data = get_meta_data(ptr, CURRENT)))
			memcpy(new_zone, ptr, size);
		else
			memcpy(new_zone, ptr, data->size);
		// memcpy(new_zone, ptr, data->size);
		// copy_block(ptr, new_zone);
		free(ptr);
		return (new_zone);
	}
	// write(1, " DONE\n", 6);
	return (NULL);
}

