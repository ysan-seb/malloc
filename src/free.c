/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 18:59:58 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/09/19 19:00:18 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		free(void *ptr)
{
	int size;

	if (pthread_mutex_lock(&g_lock) != 0)
		return ;
	if (!g_zones.checked)
		check_var_env();
	size = ft_free(ptr);
	if (size > 0 && g_zones.v)
		malloc_print("FREE", size, ptr);
	if (pthread_mutex_unlock(&g_lock) != 0)
		return ;
	return ;
}
