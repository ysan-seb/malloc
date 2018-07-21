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

void *malloc(size_t size)
{
	void *ptr;
	size_t len;

	if (size == 0)
		return (NULL);
	// if (size < TINY)
		// ptr = g_tslzone.tiny.ptr;
	// else if (size > TINY && size < SMALL)
		// ptr = g_tslzone.small.ptr;
	// else
		// ptr = g_tslzone.large.ptr;
	
	len = (size - 1) / getpagesize() + 1;
	g_tslzone.large.size = len;
	if ((g_tslzone.large.ptr = mmap(NULL, len * getpagesize(), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
		return (NULL);
	return (g_tslzone.large.ptr);
}
