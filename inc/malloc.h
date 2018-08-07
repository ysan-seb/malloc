#ifndef MALLOC_H
# define MALLOC_H

# define FIRST		1
# define PREV 		2
# define CURRENT 	3
# define NEXT 		4
# define LAST 		5

# define TINY		  128
# define SMALL		2048

#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>
#include <stdio.h>

typedef struct		s_zone
{
	void			*ptr;  // first ptr large zone else ptr block after metadata
	size_t			size; // size for large else size by block
	size_t			free; // freespace large else free status
	struct s_zone	*next;
}					t_zone;

// typedef struct		s_zone
// {
// 	void			*align;
// 	void			*ptr; // first ptr tiny small zone
// 	size_t			size; // zone size
// 	size_t			free; // zone freespace
// 	t_block			*block; // tiny & small block
// 	struct s_zone	*next;
// }					t_zone;

typedef struct		s_zones
{
	t_zone			*tiny;
	t_zone			*small;
	t_zone			*large;
}					t_zones;

t_zones				g_zones;

int debug;

void				free(void *ptr);
void				*malloc(size_t size);
void				*calloc(size_t nmemb, size_t size);
void				*realloc(void *ptr, size_t size);
void				show_alloc_mem(void);

void       *valloc(size_t size);

int					ft_strlen(char *str);
void				ft_putchar(char c);
void				ft_putstr(char *str);
void				ft_putnbr(int n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_putptr(void *ptr);
void	      *ft_memset(void *b, int c, size_t len);

t_zone      *get_ptr(void *ptr);
void				*malloc_tiny(size_t size);
void				*malloc_small(size_t size);
void				*malloc_large(size_t size);
void				free_tiny(t_zone *zone, void *ptr);
void				free_small(t_zone *zone, void *ptr);
void				free_large(t_zone *zone, void *ptr);

#endif



/*
   TINY
   {[m][d] -> [m][d] -> [m][d] -> [m][d] -> [][][][][][][][][]} -> next

   SMALL
   {[m][d] -> [m][d] -> [m][d] -> [m][d] -> [][][][][][][][][]} -> next

   LARGE
   {[m][d]} -> next


   {[][][][]} zone ptr free_space next
   [] block ptr size free next

 */
