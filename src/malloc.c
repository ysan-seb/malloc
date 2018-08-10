/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yann <yann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 11:50:43 by yann              #+#    #+#             */
/*   Updated: 2018/08/10 21:41:10 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t	align(size_t size)
{
	return ((size % 16 != 0) ? size += 16 - (size % 16) : size);
}

void			*malloc(size_t size)
{
	size = align(size);
	if (size == 0)
		return (malloc(16));
	if (size < TINY)
		return (malloc_tiny(size));
	else if (size > TINY && size < SMALL)
		return (malloc_small(size));
	else
		return (malloc_large(size));
}
