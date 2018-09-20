#include "malloc.h"

static void				print_alloc_mem(t_zone *zone, char type)
{
	if (zone->free == 1)
        ft_putstr("\e[1;48;5;240m");		
    else if (type == 'T')
        ft_putstr("\e[1;38;5;232m\e[42m");
    else if (type == 'S')
        ft_putstr("\e[1;38;5;232m\e[43m");
    else
	    ft_putstr("\e[1;38;5;232m\e[41m");
	write(1, "|", 1);
	ft_putnbr(zone->size);
	ft_putstr("\e[0m");	
}

static void			show_map(t_zone *map, char type)
{
	t_zone	*zone;

	if (!map)
		return ;
	while (map)
	{
		zone = map->ptr;
		while (zone)
		{
			print_alloc_mem(zone, type);
			zone = zone->next;
		}
		map = map->next;
		ft_putstr("\e[0m");		
	}
}

static void			show_zone(t_zone *zone, char type)
{
	if (!zone)
		return ;
	while (zone)
	{
		print_alloc_mem(zone, type);
		zone = zone->next;
	}
	ft_putstr("\e[0m");
}

static void				ft_show_graph_mem(void)
{
	t_zone *tiny;
	t_zone *small;
	t_zone *large;

	tiny = g_zones.tiny;
	small = g_zones.small;
	large = g_zones.large;
	show_map(tiny, 'T');
	show_map(small, 'S');
	show_zone(large, 'L');
}

void    show_graph_mem()
{
	show_alloc_mem();
    ft_show_graph_mem();
}