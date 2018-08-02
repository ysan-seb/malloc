#include "malloc.h"

int i = 0;

static t_zone   *create_large_zone(size_t size)
{
        void	*ptr;
        size_t	len;
        t_zone 	*zone;
        int 	pagesize;

    	pagesize = getpagesize();
    	len = (size + sizeof(t_zone) - 1) / pagesize + 1;
		if ((ptr = mmap(0, len * pagesize, PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
			return (NULL);
		zone = ptr;
		zone->size = size;
		zone->free = 0;
		zone->ptr = ptr + sizeof(t_zone);
		zone->next = NULL;
		g_zones.large = zone;
        i += len;
        // ft_putptr(zone->ptr);
        // ft_putchar('\n');
		return (zone->ptr);
}

static t_zone   *create_large_zone_next(size_t size, t_zone *zone)
{
        void	*ptr;
        size_t	len;
        int 	pagesize;

    	pagesize = getpagesize();
    	len = (size + sizeof(t_zone) - 1) / pagesize + 1;
        if ((ptr = mmap(0, len * pagesize, PROT_READ | PROT_WRITE
        ,MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
            return (NULL);
        while (zone->next)
            zone = zone->next;
        zone->next = ptr;
        zone = zone->next;
        zone->size = size;
        zone->free = 0;
        zone->ptr = ptr + sizeof(t_zone);
        zone->next = NULL;
        i += len;
        // ft_putptr(zone->ptr);
        // ft_putchar('\n');
        return (zone->ptr);
}

void		*malloc_large(size_t size)
{
	t_zone 	*zone;

    // ft_putstr("\e[1;38;5;1m");
	// write(1,"LMALLOC ", 8);
    // ft_putstr("\e[0m");
    // ft_putnbr(i);
    // ft_putchar('\n');
	zone = g_zones.large;
	if (size == 0)
		return (malloc(16));
	if (!zone)
        return (create_large_zone(size));
	else
        return (create_large_zone_next(size, zone));
}