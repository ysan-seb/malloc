#ifndef MALLOC_H
# define MALLOC_H

# define FIRST		1
# define PREV 		2
# define CURRENT 	3
# define NEXT 		4
# define LAST 		5

#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>


#include <stdio.h>
 #include <string.h>

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
void   				*calloc(size_t nmemb, size_t size);
void				*ft_realloc(void *ptr, size_t size);
void				show_alloc_mem(void);

t_zone		*get_meta_data(void *ptr, int param);
void		*alloc(size_t size, size_t len, int pagesize);
int		ft_strlen(char *str);
void	ft_putstr(char *str);
void	ft_putchar(char c);
void	ft_putnbr(int n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void		ft_putptr(void *ptr);

#endif
