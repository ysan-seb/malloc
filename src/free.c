#include "malloc.h"

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
	t_zone  *map;
	t_zone	*zone;

	map = g_zones.small;
	if (!map)
		return (get_ptr_in_large_zone(ptr));
	else
	{
		while (map)
		{
			zone = map->ptr;
			while (zone) 
			{
				if (zone->ptr == ptr)
					return (zone);
				zone = zone->next;
			}
			map = map->next;
		}
	}
	return (get_ptr_in_large_zone(ptr));
}

static t_zone	*get_ptr_in_tiny_zone(void *ptr)
{
	t_zone  *map;
	t_zone	*zone;

	map = g_zones.tiny;
	if (!map)
		return (get_ptr_in_small_zone(ptr));
	else
	{
		while (map)
		{
			zone = map->ptr;
			while (zone) 
			{
				if (zone->ptr == ptr)
					return (zone);
				zone = zone->next;
			}
			map = map->next;
		}
	}
	return (get_ptr_in_small_zone(ptr));
}

// static int	check_pointer(void *ptr)
// {
// 	t_zone *zone;

// 	zone = g_zone;
// 	if (!zone)
// 		return (0);
// 	else
// 	{
// 		while (zone)
// 		{
// 			if (zone->ptr == ptr)
// 				return (1);
// 			zone = zone->next;
// 		}
// 	}
// 	return (0);
// }

void		free(void *ptr)
{
	t_zone *zone;

    (debug) ? ft_putstr("\e[1;38;5;!m") : 0;
	(debug) ? write(1,"FREE     ", 8) : 0;
    (debug) ? ft_putstr("\e[0m") : 0;
	if (!ptr)
	{
		(debug) ? ft_putstr("PTR_IS_NULL\n") : 0;
		return;
	}
	if (!(zone = get_ptr_in_tiny_zone(ptr)))
	{
		(debug) ? ft_putstr("PTR_NOT_MINE\n") : 0;
		return;
	}
	(debug) ? ft_putptr(ptr) : 0;
	(debug) ? ft_putchar('\n') : 0;
	if (zone->size < TINY)
		free_tiny(zone, ptr);
	else if (zone->size > TINY && zone->size < SMALL)
		free_small(g_zones.small, ptr);
	else
		free_large(g_zones.large, ptr);
}

