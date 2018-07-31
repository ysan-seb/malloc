#include "malloc.h"

t_zone		*meta_data(void *ptr)
{
	char *tmp;
	tmp = ptr;
	return (ptr = tmp -= sizeof(t_zone));
}

t_zone		*get_meta_data(void *ptr, int param)
{
	t_zone *zone;

	zone = g_zone;
	if (zone)
	{
		if (param == FIRST)
			return (zone);
		while (zone->next)
		{
			if (param == PREV && zone->next->ptr == ptr)
				return (zone);
			else if (param == CURRENT && zone-> ptr == ptr)
				return (zone);
			else if (param == NEXT && zone->next->ptr == ptr)
			{
				zone = zone->next;
				return (zone);		
			}
			zone = zone->next;
		}
		if (param == LAST)
			return (zone);
	}
	return (NULL);
}

size_t		align(size_t size)
{
	return ((size % 16 != 0) ? size += 16 - (size % 16) : size);
}

void		*malloc(size_t size)
{
	void	*ptr;
	size_t	len;
	t_zone 	*zone = NULL;
	int 	pagesize;

	zone = g_zone;
	pagesize = getpagesize();
	size = align(size);
	len = (size + sizeof(t_zone) - 1) / pagesize + 1;

	// write(1, "MALLOC  : ", 10);
	// ft_putstr("\e[1;38;5;4m");
	// ft_putnbr(size);
	// ft_putstr("\e[1;38;5;9m");
	// ft_putnbr(len);
	// ft_putstr("\e[0m");	

	if (size == 0)
		return (malloc(16));
	if (!zone)
	{
		if ((ptr = mmap(0, len * pagesize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
			return (NULL);
		zone = ptr;
		zone->size = size;
		zone->free = 0;
		zone->ptr = ptr + sizeof(t_zone);
		zone->next = NULL;
		g_zone = zone;
		// ft_putptr(zone->ptr);
		// write(1, " DONE\n", 6);
		return (zone->ptr);
	} 
	else
	{
		if ((ptr = mmap(0, len * pagesize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
			return (NULL);
		while (zone->next)
			zone = zone->next;
		zone->next = ptr;
		zone = zone->next;
		zone->size = size;
		zone->free = 0;
		zone->ptr = ptr + sizeof(t_zone);
		zone->next = NULL;
		// ft_putptr(zone->ptr);
		// write(1, " DONE\n", 6);
		return (zone->ptr);
	}
}