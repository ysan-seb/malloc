/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 16:20:38 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/07/14 20:38:51 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# define TINY 1024
# define SMALL 2048

# include <sys/mman.h>
# include <stdlib.h>
# include <unistd.h>

// typedef struct			s_block
// {
// 	int					*ptr;
// 	int 				free;
// 	size_t				size;
// 	struct s_block		*next;
// }						t_block;

// typedef struct			s_zone
// {
// 	int					*ptr;
// 	size_t				size;
// 	t_block				block;
// 	struct s_zone		*next;
// }						t_zone;

// typedef struct			s_tslzone
// {
// 	t_zone				tiny;
// 	t_zone				small;
// 	t_zone				large;
// }						t_tslzone;

// t_tslzone				g_tslzone;

typedef struct		s_zone
{
	int				free;
	size_t			size;
	struct s_zone 	*next;
}					t_zone;

t_zone				g_zone;

void					free(void *ptr);
void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);
void					show_alloc_mem();

#endif
