#include "malloc.h"

int j = 0;

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

static t_zone   *create_tiny_zone(size_t size)
{
        void	*ptr;
        size_t	len;
        t_zone 	*zone;
        int 	pagesize;

        // write(1, " Create new\n", 13);
    	pagesize = getpagesize();
    	len = ((100 * TINY + 100 * sizeof(t_zone)) - 1) / pagesize + 1;
		if ((ptr = mmap(0, len * pagesize, PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
			return (NULL);
		zone = ptr;
		zone->size = size;
		zone->free = 0;
		zone->ptr = ptr + sizeof(t_zone);
		zone->next = NULL;
		g_zones.tiny = zone;
        j += len;
        get_zone_size(len * pagesize, '+');
        get_zone_size(size + sizeof(t_zone), '-');
        // ft_putptr(zone->ptr);
        // ft_putchar('\n');
		return (zone->ptr);
}

static t_zone   *create_tiny_zone_next(size_t size, t_zone *zone)
{
        void	*ptr;
        size_t	len;
        int 	pagesize;

        j++;
        // write(1, " Create next\n", 14);
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
        // ft_putptr(zone->ptr);
        // ft_putchar('\n');
        return (zone->ptr);
}

void        *fill_tiny_zone(size_t size)
{
    t_zone  *zone;
    void     *ptr;
    zone = g_zones.tiny;
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
        get_zone_size(size + sizeof(t_zone), '-');
        // ft_putptr(zone->ptr);
        // ft_putchar('\n');
        return (zone->ptr);
    }
    return (NULL);
}

void		*malloc_tiny(size_t size)
{
    int zonesize;
	t_zone 	*zone;

    zonesize = get_zone_size(0, 0);
    // ft_putstr("\e[1;38;5;2m");
	// write(1,"MALLOC ", 8);
    // ft_putstr("\e[0m");
	zone = g_zones.tiny;
    // ft_putnbr(j);
	if (size == 0)
		return (malloc(16));
	if (!zone)
        return (create_tiny_zone(size));
	else
    {
        int newsize = size + sizeof(t_zone);
    // ft_putnbr(size);
    // ft_putstr("\e[1;38;5;3m");
    //     ft_putnbr(newsize);
    // ft_putstr("\e[0m");
    // ft_putnbr(zonesize);


        if ((zonesize - newsize) > 0)
            return (fill_tiny_zone(size));
        else
            return (create_tiny_zone_next(size, zone));
    }
    return (NULL);
}