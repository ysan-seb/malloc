#include "malloc.h"

int i = 0;

static size_t       get_zone_size(size_t size, char arg)
{
    static int zone_size;

    if (arg == '+')
        zone_size += size;
    else if (arg == '-' && zone_size - size > 0)
        zone_size -= size;
    else if (arg == 's')
        zone_size = size;
    return (zone_size);
}

static t_zone   *create_small_zone(size_t size)
{
        void	*ptr;
        size_t	len;
        t_zone 	*zone;
        int 	pagesize;

    	pagesize = getpagesize();
    	len = ((100 * SMALL + 100 * sizeof(t_zone)) - 1) / pagesize + 1;
		if ((ptr = mmap(0, len * pagesize, PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
			return (NULL);
		zone = ptr;
		zone->size = size;
		zone->free = 0;
		zone->ptr = ptr + sizeof(t_zone);
		zone->next = NULL;
		g_zones.small = zone;
        i += len;
        get_zone_size(len * pagesize, '+');
        get_zone_size(size + sizeof(t_zone), '-');
        (debug) ? ft_putptr(zone->ptr) : 0;
        (debug) ? ft_putchar('\n') : 0;
		return (zone->ptr);
}

static t_zone   *create_small_zone_next(size_t size, t_zone *zone)
{
        void	*ptr;
        size_t	len;
        int 	pagesize;

        i++;
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
        get_zone_size(len * pagesize, 's');
        get_zone_size(size + sizeof(t_zone), '-');
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
        while(zone->next)
            zone = zone->next;
        zone->next = zone->ptr + zone->size;
        zone = zone->next;
        // ft_putptr(zone);
        // ft_putchar('\n');
        ptr = zone;
        // ft_putptr(zone);
        // ft_putnbr(zone->size);
        zone->ptr = ptr + sizeof(t_zone);
        zone->size = size;
        zone->next = NULL;
        get_zone_size(size + sizeof(t_zone), '-');
        // ft_putptr(zone->ptr);
        // ft_putchar('\n');
        return (zone->ptr);
    }
    return (NULL);
}

void        *check_space(size_t size)
{
    void    *ptr;
    t_zone *zone;
    
    zone = g_zones.small;
    if (zone)
    {
        if (zone->free == 1 && zone->size >= size)
        {
            // write(1, "give1\n", 5);
            zone->free = 0;
            ptr = zone->ptr;
            bzero(zone->ptr, zone->size);
            return (ptr);
        }
        while (zone->next)
        {
            zone = zone->next;
            if (zone->free == 1 && zone->size >= size)
            {
                // write(1, "give2\n", 6);
                zone->free = 0;
                ptr = zone->ptr;
                return (ptr);
            }
        }
    }
    // write(1, "no\n", 3);
    // show_alloc_mem();
    return (NULL);
}

void		*malloc_small(size_t size)
{
    int zonesize;
    void  *res;
	t_zone 	*zone;

    zonesize = get_zone_size(0, 0);
    (debug) ? ft_putstr("\e[1;38;5;3m") : 0;
	(debug) ? write(1,"MALLOC  ", 9) : 0;
    (debug) ? ft_putstr("\e[0m") : 0;
	zone = g_zones.small;

    // ft_putnbr(i);
	if (size == 0)
		return (malloc(16));
	if (!zone)
        return (create_small_zone(size));
	else
    {
        // ft_putnbr(zonesize);
        // // ft_putchar('\n');
        // int newsize = size + sizeof(t_zone);

        // if ((zonesize - newsize) > 0)
        //     return (fill_small_zone(size));
        // else if ((res = check_space(size)))
        //     return (res);
        // else
            return (create_small_zone_next(size, zone));
    }
    return (NULL);
}