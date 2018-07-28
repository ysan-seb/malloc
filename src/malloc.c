#include "malloc.h"

void		*malloc(size_t size)
{
	void	*ptr;
	size_t	len;
	t_zone 	*zone;
	int 	pagesize;

	zone = g_zone;
	pagesize = getpagesize();
	len = (size + sizeof(t_zone) - 1) / pagesize + 1;
	write(1, "MALLOC  : ", 10);
	ft_putstr("\e[1;38;5;4m");
	ft_putnbr(size);
	ft_putstr("\e[1;38;5;9m");
	ft_putnbr(len);
	ft_putstr("\e[0m");	
	if (size == 0)
		return (NULL);
	if (!zone)
	{
		if ((zone = mmap(NULL, len * pagesize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
			return (NULL);
		zone->size = size;
		zone->free = 0;
		zone->ptr = zone + sizeof(t_zone);
		zone->next = NULL;
		g_zone = zone;
		ft_putptr(zone->ptr);
		write(1, " DONE\n", 6);
		return (zone->ptr);
	} 
	else
	{
		if ((ptr = mmap(NULL, len * pagesize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
			return (NULL);
		while (zone->next)
			zone = zone->next;
		zone->next = ptr;
		zone = zone->next;
		zone->size = size;
		zone->free = 0;
		zone->ptr = zone + sizeof(t_zone);
		zone->next = NULL;
		ft_putptr(zone->ptr);
		write(1, " DONE\n", 6);
		return (zone->ptr);
	}
}