/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yann <yann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 11:47:56 by yann              #+#    #+#             */
/*   Updated: 2018/08/10 21:29:28 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		ft_free(void *ptr)
{
	t_zone	*zone;
	size_t	size;

	if (!ptr)
		return (0);
	if (!(zone = get_ptr(ptr)))
		return (0);
	size = zone->size;
	if (zone->size < TINY)
		free_tiny(zone);
	else if (zone->size > TINY && zone->size < SMALL)
		free_small(zone);
	else
		free_large(g_zones.large, ptr);
	return (size);
}
