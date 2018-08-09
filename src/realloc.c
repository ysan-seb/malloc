/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yann <yann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 11:45:36 by yann              #+#    #+#             */
/*   Updated: 2018/08/08 11:45:40 by yann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*realloc(void *ptr, size_t size)
{
	t_zone	*data;
	void	*new_ptr;

	if (!ptr)
		return (malloc(size));
	else if (ptr && size == 0)
		free(ptr);
	else if (!(data = get_ptr(ptr)))
		return (NULL);
	else
	{
		if (!(new_ptr = malloc(size)))
			return (NULL);
		ft_memcpy(new_ptr, ptr, data->size);
		free(ptr);
		return (new_ptr);
	}
	return (NULL);
}

