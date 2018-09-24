/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_small.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yann <yann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 11:49:05 by yann              #+#    #+#             */
/*   Updated: 2018/08/10 21:39:02 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_zone			*create_small_zone(size_t size)
{
	void	*ptr;
	size_t	len;
	t_zone	*map;
	t_zone	*zone;
	int		pagesize;

	pagesize = getpagesize();
	len = ((100 * SMALL + 100 * sizeof(t_zone)) + sizeof(t_zone) - 1)
		/ pagesize + 1;
	if ((ptr = mmap(0, len * pagesize, PROT_READ | PROT_WRITE,
					MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
		return (NULL);
	map = ptr;
	map->size = len * pagesize;
	map->free = map->size - (size + (sizeof(t_zone) * 2));
	map->ptr = (void*)map + sizeof(t_zone);
	map->next = NULL;
	zone = map->ptr;
	zone->ptr = (void*)map->ptr + sizeof(t_zone);
	zone->size = size;
	zone->free = 0;
	zone->next = NULL;
	g_zones.small = (void*)map;
	return (zone->ptr);
}

static t_zone			*create_small_zone_next(size_t size, t_zone *map)
{
	void	*ptr;
	size_t	len;
	t_zone	*zone;
	int		pagesize;

	pagesize = getpagesize();
	len = ((100 * SMALL + 100 * sizeof(t_zone)) + sizeof(t_zone) - 1)
		/ pagesize + 1;
	if ((ptr = mmap(0, len * pagesize, PROT_READ | PROT_WRITE,
					MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
		return (NULL);
	while (map->next)
		map = map->next;
	map->next = ptr;
	map = map->next;
	map->ptr = (void*)map + sizeof(t_zone);
	map->size = len * pagesize;
	map->free = map->size - (size + (sizeof(t_zone) * 2));
	map->next = NULL;
	zone = (void*)map->ptr;
	zone->ptr = (void*)map->ptr + sizeof(t_zone);
	zone->size = size;
	zone->free = 0;
	zone->next = NULL;
	return (zone->ptr);
}

static void				*fill_small_free(size_t size)
{
	t_zone	*map;
	t_zone	*zone;

	map = g_zones.small;
	if (!map)
		return (NULL);
	while (map)
	{
		zone = map->ptr;
		while (zone)
		{
			if (zone->free == 1 && zone->size >= size)
			{
				zone->free = 0;
				return (zone->ptr);
			}
			zone = zone->next;
		}
		map = map->next;
	}
	return (NULL);
}

static void				*fill_small_zone(size_t size)
{
	t_zone	*map;
	t_zone	*zone;

	map = g_zones.small;
	while (map)
	{
		zone = map->ptr;
		if ((size + sizeof(t_zone)) <= map->free)
		{
			while (zone->next)
				zone = zone->next;
			zone->next = (void*)zone->ptr + zone->size;
			zone = zone->next;
			zone->ptr = (void*)zone + sizeof(t_zone);
			zone->size = size;
			zone->free = 0;
			zone->next = NULL;
			map->free -= (size + sizeof(t_zone));
			return (zone->ptr);
		}
		map = map->next;
	}
	return (NULL);
}

void					*malloc_small(size_t size)
{
	t_zone	*map;
	void	*ptr;

	map = g_zones.small;
	if (size == 0)
		return (malloc(16));
	if (!map)
		return (create_small_zone(size));
	else
	{
		if ((ptr = fill_small_free(size)))
			return (ptr);
		if ((ptr = fill_small_zone(size)))
			return (ptr);
		else
			return (create_small_zone_next(size, map));
	}
}
