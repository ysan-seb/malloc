/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defrag.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 16:51:45 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/09/22 16:54:49 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		defragmentation(t_zone *map)
{
	t_zone	*zone;

	while (map)
	{
		zone = map->ptr;
		while (zone)
		{
			if (zone->free == 1 && zone->next && zone->next->free == 1)
			{
				zone->size += sizeof(t_zone) + zone->next->size;
				zone->next = zone->next->next;
			}
			zone = zone->next;
		}
		map = map->next;
	}
}
