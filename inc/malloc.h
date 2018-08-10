/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yann <yann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 11:50:58 by yann              #+#    #+#             */
/*   Updated: 2018/08/10 22:09:26 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# define TINY		128
# define SMALL		2048

# include <sys/mman.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct		s_zone
{
	void			*ptr;
	size_t			size;
	size_t			free;
	struct s_zone	*next;
}					t_zone;

typedef struct		s_zones
{
	t_zone			*tiny;
	t_zone			*small;
	t_zone			*large;
}					t_zones;

t_zones				g_zones;

void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				show_alloc_mem(void);

int					ft_strlen(char *str);
void				ft_putchar(char c);
void				ft_putstr(char *str);
void				ft_putnbr(int n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_putptr(void *ptr);
void				*ft_memset(void *b, int c, size_t len);

t_zone				*get_ptr(void *ptr);
void				*malloc_tiny(size_t size);
void				*malloc_small(size_t size);
void				*malloc_large(size_t size);
void				free_tiny(t_zone *zone);
void				free_small(t_zone *zone);
void				free_large(t_zone *zone, void *ptr);

#endif
