/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 14:18:30 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/09/22 16:49:50 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	show_alloc_mem(void)
{
	if (pthread_mutex_lock(&g_lock) != 0)
		return ;
	if (!g_zones.checked)
		check_var_env();
	ft_show_alloc_mem();
	if (pthread_mutex_unlock(&g_lock) != 0)
		return ;
}
