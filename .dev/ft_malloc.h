#ifndef FT_MALLOC_H
# define FT_MALLOC_H

#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

typedef struct		s_zone
{
	void			*ptr;
	size_t			size;
	size_t			free;
	struct s_zone	*next;
}					t_zone;

t_zone				*g_zone;

void				ft_free(void *ptr);
void				*ft_malloc(size_t size);
void				show_alloc_mem(void);

#endif
