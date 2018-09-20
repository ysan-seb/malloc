/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 18:18:18 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/09/19 19:00:50 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (pthread_mutex_lock(&g_lock) != 0)
		return (NULL);
	if (!g_zones.checked)
		check_var_env();
	new_ptr = ft_realloc(ptr, size);
	if (g_zones.v)
		malloc_print("REALLOC", size, new_ptr);
	if (pthread_mutex_unlock(&g_lock) != 0)
		return (NULL);
	return (new_ptr);
}
