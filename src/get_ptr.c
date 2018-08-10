/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ptr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yann <yann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 11:47:44 by yann              #+#    #+#             */
/*   Updated: 2018/08/10 21:52:17 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_zone	*get_ptr_in_large_zone(void *ptr)
{
	t_zone	*zone;

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
	t_zone	*map;
	t_zone	*zone;

	map = g_zones.small;
	if (!map)
		return (get_ptr_in_large_zone(ptr));
	else
	{
		while (map)
		{
			if (!map || !map->ptr)
				return (get_ptr_in_large_zone(ptr));
			zone = map->ptr;
			while (zone)
			{
				if (zone->ptr == ptr)
					return (zone);
				zone = zone->next;
			}
			map = map->next;
		}
	}
	return (get_ptr_in_large_zone(ptr));
}

static t_zone	*get_ptr_in_tiny_zone(void *ptr)
{
	t_zone	*map;
	t_zone	*zone;

	map = g_zones.tiny;
	if (!map)
		return (get_ptr_in_small_zone(ptr));
	else
	{
		while (map)
		{
			zone = map->ptr;
			while (zone)
			{
				if (zone->ptr == ptr)
					return (zone);
				zone = zone->next;
			}
			map = map->next;
		}
	}
	return (get_ptr_in_small_zone(ptr));
}

t_zone			*get_ptr(void *ptr)
{
	return (get_ptr_in_tiny_zone(ptr));
}
