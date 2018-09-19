/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 16:17:32 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/09/19 19:02:08 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if ((count * size) == 0)
		return (ft_malloc(0));
	ptr = ft_malloc(count * size);
	ft_memset(ptr, 0, count * size);
	return (ptr);
}
