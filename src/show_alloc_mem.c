/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yann <yann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 11:50:50 by yann              #+#    #+#             */
/*   Updated: 2018/08/10 22:02:32 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int					nb_len_base(int value, int base)
{
	int		len;
	double	pow;

	len = 0;
	pow = 1;
	if (value < 0 && base == 10)
		len++;
	(value < 0) ? value = -value : 0;
	while (value >= (pow *= base))
		len++;
	return (len + 1);
}

void				ft_itoa_base(int value, int base)
{
	char	s[13];
	int		len;

	if (base < 2 || base > 16)
		return ;
	len = nb_len_base(value, base);
	s[len] = '\0';
	if (value < 0 && base == 10)
		s[0] = '-';
	(value < 0) ? value = -value : 0;
	if (value == 0)
	{
		s[0] = '0';
		s[1] = '\0';
		ft_putstr(s);
	}
	while (value)
	{
		s[--len] = (value % base > 9) ? value % base - 10 + 'A'
			: value % base + '0';
		value /= base;
	}
	ft_putstr(s);
}

void				print_alloc_mem(t_zone *zone)
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
	ft_putstr(zone_type);
	ft_putstr(" : 0x");
	ft_itoa_base((int)map->ptr, 16);
	ft_putchar('\n');
	while (map)
	{
		zone = map->ptr;
		while (zone)
		{
			print_alloc_mem(zone);
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
	ft_putstr(" : 0x");
	ft_itoa_base((int)zone, 16);
	ft_putchar('\n');
	while (zone)
	{
		print_alloc_mem(zone);
		zone = zone->next;
	}
}

void				show_alloc_mem(void)
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
