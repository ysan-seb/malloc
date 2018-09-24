/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yann <yann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 11:50:50 by yann              #+#    #+#             */
/*   Updated: 2018/09/24 15:26:29 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void			print_alloc_mem_color(t_zone *zone)
{
	ft_putstr("\e[1;38;5;4m");
	ft_putstr("0x");
	ft_itoa_base((int)zone->ptr, 16);
	ft_putstr("\e[0m");
	ft_putstr(" - ");
	ft_putstr("\e[1;38;5;4m");
	ft_putstr("0x");
	ft_itoa_base((int)zone->ptr + zone->size, 16);
	ft_putstr("\e[0m");
	ft_putstr(" : ");
	if (zone->size <= TINY)
		ft_putstr("\e[1;38;5;2m");
	else if (zone->size > TINY && zone->size <= SMALL)
		ft_putstr("\e[1;38;5;3m");
	else
		ft_putstr("\e[1;38;5;1m");
	ft_putnbr(zone->size);
	ft_putstr("\e[0m");
	ft_putstr(" octets\n");
}

static void			print_alloc_mem(t_zone *zone)
{
	ft_putstr("0x");
	ft_itoa_base((int)zone->ptr, 16);
	ft_putstr(" - ");
	ft_putstr("0x");
	ft_itoa_base((int)zone->ptr + zone->size, 16);
	ft_putstr(" : ");
	ft_putnbr(zone->size);
	ft_putstr(" octets\n");
}

static void			show_map(t_zone *map, char *zone_type)
{
	t_zone	*zone;

	if (!map)
		return ;
	while (!zones_is_filled(map->ptr))
		if (!(map = map->next))
			return ;
	ft_putstr(zone_type);
	ft_putstr(" : ");
	(g_zones.s_color) ? ft_putstr("\e[1;38;5;4m0x") : ft_putstr("0x");
	ft_itoa_base((int)map->ptr, 16);
	(g_zones.s_color) ? ft_putstr("\e[0m\n") : ft_putchar('\n');
	while (map)
	{
		zone = map->ptr;
		while (zone)
		{
			if (zone->free == 0 && !g_zones.s_color)
				print_alloc_mem(zone);
			else if (zone->free == 0 && g_zones.s_color)
				print_alloc_mem_color(zone);
			zone = zone->next;
		}
		map = map->next;
	}
}

static void			show_zone(t_zone *zone, char *zone_type)
{
	if (!zone)
		return ;
	ft_putstr(zone_type);
	ft_putstr(" : ");
	(g_zones.s_color) ? ft_putstr("\e[1;38;5;4m") : 0;
	ft_putstr("0x");
	ft_itoa_base((int)zone, 16);
	(g_zones.s_color) ? ft_putstr("\e[0m") : 0;
	ft_putchar('\n');
	while (zone)
	{
		if (zone->free == 0 && !g_zones.s_color)
			print_alloc_mem(zone);
		else if (zone->free == 0 && g_zones.s_color)
			print_alloc_mem_color(zone);
		zone = zone->next;
	}
}

void				ft_show_alloc_mem(void)
{
	t_zone *tiny;
	t_zone *small;
	t_zone *large;

	tiny = g_zones.tiny;
	small = g_zones.small;
	large = g_zones.large;
	show_map(tiny, "TINY");
	show_map(small, "SMALL");
	show_zone(large, "LARGE");
}
