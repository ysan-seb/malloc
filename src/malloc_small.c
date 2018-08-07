#include "malloc.h"

static t_zone   *create_small_zone(size_t size)
{
        void	*ptr;
        size_t	len;
        t_zone 	*map;
        t_zone  *zone;
        int 	pagesize;

        // write(1, " Create new\n", 13);
    	pagesize = getpagesize();
    	len = ((100 * SMALL + 100 * sizeof(t_zone)) - 1) / pagesize + 1;
		if ((ptr = mmap(0, len * pagesize, PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
			return (NULL);
		map = ptr;
		map->size = len * pagesize;
		map->free = map->size - (size + (sizeof(t_zone) * 2));
		map->ptr = (void*)map + sizeof(t_zone);
		map->next = NULL;
        zone =  map->ptr;
        zone->ptr = (void*)map->ptr + sizeof(t_zone);
        zone->size = size;
        zone->free = 0;
        zone->next = NULL; 
		g_zones.small = (void*)map;
        (debug) ? ft_putptr(zone->ptr) : 0;
        (debug) ? ft_putchar('\n') : 0;
		return (zone->ptr);
}

static t_zone   *create_small_zone_next(size_t size, t_zone *map)
{
        void	*ptr;
        size_t	len;
        t_zone  *zone;
        int 	pagesize;
        // write(1, " Create next\n", 14);
    	pagesize = getpagesize();
    	len = (size + sizeof(t_zone) - 1) / pagesize + 1;
        if ((ptr = mmap(0, len * pagesize, PROT_READ | PROT_WRITE
        ,MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
            return (NULL);
        while (map->next)
            map = map->next;
        map->next = ptr;
        map = map->next;
        map->ptr = (void*)map + sizeof(t_zone);
        map->size = len * pagesize;
        map->free = map->size - (size + (sizeof(t_zone) * 2));
        map->next = NULL;
        zone =  (void*)map->ptr;
        zone->ptr = (void*)map->ptr + sizeof(t_zone);
        zone->size = size;
        zone->free = 0;
        zone->next = NULL; 
        (debug) ? ft_putptr(zone->ptr) : 0;
        (debug) ? ft_putchar('\n') : 0;
        return (zone->ptr);
}

void        *fill_small_zone(size_t size)
{
    t_zone  *zone;
    void     *ptr;
    zone = g_zones.small;
    if (zone)
    {
        // write(1, " fill\n", 6);
        while(zone->next)
            zone = zone->next;
        zone->next = zone->ptr + zone->size;
        zone = zone->next;
        ptr = zone;
        zone->ptr = ptr + sizeof(t_zone);
        zone->size = size;
        zone->next = NULL;
        ft_putptr(zone->ptr);
        ft_putchar('\n');
        return (zone->ptr);
    }
    return (NULL);
}

void		*malloc_small(size_t size)
{
    int zonesize;
	t_zone 	*map;

    (debug) ? ft_putstr("\e[1;38;5;2m") : 0 ;
	(debug) ? write(1,"MALLOC  ", 9) : 0;
    (debug) ? ft_putstr("\e[0m") : 0;
	map = g_zones.small;
    // ft_putnbr(j);
	if (size == 0)
		return (malloc(16));
	if (!map)
        return (create_small_zone(size));
	// else
    // {
    //     int newsize = size + sizeof(t_zone);
    // // ft_putnbr(size);
    // // ft_putstr("\e[1;38;5;3m");
    // //     ft_putnbr(newsize);
    // // ft_putstr("\e[0m");
    // // ft_putnbr(zonesize);


    //     if ((zonesize - newsize) > 0)
    //         return (fill_tiny_zone(size));
        else
            return (create_small_zone_next(size, map));
    // }
    // return (NULL);
}