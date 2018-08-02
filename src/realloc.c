#include "malloc.h"

// static int     need_space(size_t size1, size_t size2)
// {
//     size_t origin;
//     size_t asked;
    
// 	origin = (size1 - 1 + sizeof(t_zone)) / getpagesize() + 1;
//     asked = (size2 - 1 + sizeof(t_zone)) / getpagesize() + 1;
//     if (origin == asked || origin > asked)
//         return (0);
//     else
//         return (1);
// }


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

void copy_block(t_zone *src , t_zone *dst)
{
	unsigned char *sdata ,* ddata;
	size_t i;

	i = 0;
	sdata = src->ptr;
	ddata = dst->ptr;
	while(i * 4 < src->size && i * 4 < dst->size)
	{
		ddata[i] = sdata[i];
		i++;
	}
}

static t_zone	*get_ptr_in_large_zone(void *ptr)
{
	t_zone  *zone;

	zone = g_zones.large;
	if (!zone)
		return (NULL);
	else
	{
		while (zone)
		{
			if (zone->ptr == ptr)
				return (zone);
			zone = zone->next;
		}
	}
	return (NULL);
}

static t_zone	*get_ptr_in_small_zone(void *ptr)
{
	t_zone  *zone;

	zone = g_zones.small;
	if (!zone)
		return (get_ptr_in_large_zone(ptr));
	else
	{
		while (zone)
		{
			if (zone->ptr == ptr)
				return (zone);
			zone = zone->next;
		}
	}
	return (get_ptr_in_large_zone(ptr));
}

static t_zone	*get_ptr_in_tiny_zone(void *ptr)
{
	t_zone  *zone;

	zone = g_zones.tiny;
	if (!zone)
		return (get_ptr_in_small_zone(ptr));
	else
	{
		while (zone)
		{
			if (zone->ptr == ptr)
				return (zone);
			zone = zone->next;
		}
	}
	return (get_ptr_in_small_zone(ptr));
}


void    *realloc(void *ptr, size_t size)
{
	t_zone *data;
	void	*new_zone;

	// write(1, "REALLOC ", 8);
	// ft_putptr(ptr);
	// ft_putchar('\n');
	if (size == 0)
		return (realloc(ptr, 16));
	if (!ptr && size > 0)
		return (malloc(size));
	if (!get_ptr_in_tiny_zone(ptr))
	{
		write(1, " UNKNOWN\n", 9);
		return (NULL);
	}
	else
	{
		if (!(new_zone = malloc(size)))
			return (NULL);
			
		if (!(data = get_ptr_in_tiny_zone(ptr)))
			memcpy(new_zone, ptr, size);
		else
			memcpy(new_zone, ptr, data->size);
		free(ptr);
		return (new_zone);
	}
	return (NULL);
}

