/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zones_is_filled.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 15:28:47 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/09/24 15:29:22 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		zones_is_filled(t_zone *zone)
{
	int i;

	i = 0;
	if (!zone)
		return (0);
	while (zone)
	{
		if (zone->free == 0)
			return (1);
		zone = zone->next;
	}
	return (0);
}
