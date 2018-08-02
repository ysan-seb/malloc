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

	// write(1,"FREE\n", 5);
	if (!ptr)
		return;
	if (!(zone = get_ptr_in_tiny_zone(ptr)))
		return;
	if (zone->size < TINY)
		free_tiny(g_zones.tiny, ptr);
	else if (zone->size > TINY && zone->size < SMALL)
		free_small(g_zones.small, ptr);
	else
		free_large(g_zones.large, ptr);
}

