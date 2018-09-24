/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 18:59:11 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/09/19 18:59:37 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;

void			*malloc(size_t size)
{
	void		*ptr;

	if (pthread_mutex_lock(&g_lock) != 0)
		return (NULL);
	if (!g_zones.checked)
		check_var_env();
	ptr = ft_malloc(size);
	if (g_zones.v)
		malloc_print("MALLOC", align(size), ptr);
	if (pthread_mutex_unlock(&g_lock) != 0)
		return (NULL);
	return (ptr);
}
