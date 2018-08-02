#include "malloc.h"

size_t       get_zone_size(size_t size, char arg)
{
    static size_t zone_size;

    if (!zone_size)
        zone_size = size;
    if (arg == '+')
        zone_size += size;
    // else if (arg == '-')
    //     zone_size -= size;
    return (zone_size);
}
// static t_zone   *create_tiny_zone(size_t size)
// {
//         void	*ptr;
//         size_t	len;
//         t_zone 	*zone;
//         int 	pagesize;

//     	pagesize = getpagesize();
//     	len = ((100 * TINY + 100 * sizeof(t_block) + sizeof(t_zone)) - 1) / pagesize + 1;
// 		if ((ptr = mmap(0, len * pagesize, PROT_READ | PROT_WRITE,
//         MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
// 			return (NULL);
// 		zone = ptr;
//         zone->size = len * pagesize;
//         zone->free = zone->size - (sizeof(t_zone) + size);
// 		zone->next = NULL;
//         zone->block = ptr + sizeof(t_zone);
//         zone->block->ptr = ptr + sizeof(t_zone) + sizeof(t_block);
// 		zone->block->size = size;
// 		zone->block->free = 0;
//         zone->block->next = NULL;
// 		g_zones.tiny = zone;
// 		return (zone->block->ptr);
// }

static t_zone   *create_tiny_zone(size_t size)
{
        void	*ptr;
        size_t	len;
        t_zone 	*zone;
        int 	pagesize;

        write(1, "1\n", 2);
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
        get_zone_size(len * pagesize, 0);
        // get_zone_size(size + sizeof(t_zone), '-');
        // ft_putptr(zone->ptr);
        // ft_putchar('\n');
		return (zone->ptr);
}

static t_zone   *create_tiny_zone_next(size_t size, t_zone *zone)
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
        get_zone_size((len *pagesize) + (size + sizeof(t_zone)), '+');
        return (zone->ptr);
}

void        *fill_tiny_zone(size_t size)
{
    t_zone  *zone;
    void     *ptr;
    zone = g_zones.tiny;
    if (zone)
    {
        while(zone->next)
            zone = zone->next;
        zone->next = zone->ptr + zone->size;
        zone = zone->next;
        ptr = zone;
        zone->ptr = ptr + sizeof(t_zone);
        zone->size = size;
        zone->next = NULL;
        // get_zone_size(size + sizeof(t_zone), '-');
        // ft_putptr(zone->ptr);
        // ft_putchar('\n');
        return (zone->ptr);
    }
    // ft_putstr("plus de place\n");
    return (NULL);
}

void		*malloc_tiny(size_t size)
{
    static int i;
	t_zone 	*zone;

    i += size + sizeof(t_zone);
    // ft_putstr("\e[1;38;5;2m");
	// write(1,"TMALLOC ", 8);
    // ft_putstr("\e[1;38;5;4m");
    // ft_putnbr(get_zone_size(0, 0));
    // ft_putchar(' ');
    // ft_putstr("\e[0m");
    // ft_putnbr(get_zone_size(0, 0));
    // ft_putchar('\n');
	zone = g_zones.tiny;
	if (size == 0)
		return (malloc(16));
	if (!zone)
        return (create_tiny_zone(size));
	else
    {
        if ((get_zone_size(0, 0) + size + sizeof(t_zone)) < get_zone_size(0, 0))
            return (fill_tiny_zone(size));
        else
            return (create_tiny_zone_next(size, zone));
    }
}