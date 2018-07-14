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

# define TINY 256
# define SMALL 512

# include <sys/mman.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct			s_block
{
	int					*ptr;
	size_t				size;
	int					free;
	struct s_block		*next;
}						t_block;

typedef struct			s_zone
{
	int					*ptr;
	size_t				size;
	t_block				block;
	struct s_zone		*next;
}						t_zone;

typedef struct			s_lzone
{
	int					*ptr;
	size_t				size;
	int					free;
	struct s_lzone		*next;
}						t_lzone;

typedef struct			s_tslzone
{
	t_zone				tiny;
	t_zone				small;
	t_lzone				large;
}						t_tslzone;

void					free(void *ptr);
void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);
void					show_alloc_mem();

#endif
