#include "malloc.h"

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
	if (!(zone = get_ptr(ptr)))
	{
		(debug) ? ft_putstr("PTR_NOT_MINE\n") : 0;
		return;
	}
	(debug) ? ft_putptr(ptr) : 0;
	(debug) ? ft_putchar('\n') : 0;
	if (zone->size < TINY)
		free_tiny(zone, ptr);
	else if (zone->size > TINY && zone->size < SMALL)
		free_small(zone, ptr);
	else
		free_large(g_zones.large, ptr);
}

