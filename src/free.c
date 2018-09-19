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
	if (pthread_mutex_lock(&g_lock) != 0)
		return ;
	ft_free(ptr);
	if (pthread_mutex_unlock(&g_lock) != 0)
		return ;
	return ;
}
