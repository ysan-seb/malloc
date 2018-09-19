/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 19:00:24 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/09/19 19:00:37 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			*calloc(size_t count, size_t size)
{
	void		*ptr;

	if (pthread_mutex_lock(&g_lock) != 0)
		return (NULL);
	ptr = ft_calloc(count, size);
	if (pthread_mutex_unlock(&g_lock) != 0)
		return (NULL);
	return (ptr);
}
