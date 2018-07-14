/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 10:34:28 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/07/14 16:58:10 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*malloc(size_t size)
{
	void	*ptr;
	size_t	len;

	len = getpagesize();
	if ((ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE
					| MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
		return (NULL);
	return (ptr);
}
