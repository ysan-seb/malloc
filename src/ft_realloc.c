/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yann <yann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 11:45:36 by yann              #+#    #+#             */
/*   Updated: 2018/09/19 19:03:27 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*ft_realloc(void *ptr, size_t size)
{
	t_zone	*data;
	void	*new_ptr;

	if (!ptr)
		return (ft_malloc(size));
	else if (ptr && size == 0)
		ft_free(ptr);
	else if (!(data = get_ptr(ptr)))
		return (NULL);
	else
	{
		if (!(new_ptr = ft_malloc(size)))
			return (NULL);
		ft_memcpy(new_ptr, ptr, (data->size < size) ? data->size : size);
		ft_free(ptr);
		return (new_ptr);
	}
	return (NULL);
}
