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

void		*malloc(size_t size)
{
	void	*ptr;
	size_t	len;
	t_zone 	*zone = NULL;
	int 	pagesize;

	zone = g_zone;
	pagesize = getpagesize();
	if (size % 16 != 0)
		size += 16 - (size % 16);
	len = (size + sizeof(t_zone) - 1) / pagesize + 1;

	// if (size == 3312)
	// {
	// 	ft_putnbr(len);
	// 	ft_putchar(' ');
	// 	ft_putnbr(size);
	// 	ft_putchar('\n');
	// 	return (NULL);
	// }
	write(1, "MALLOC  : ", 10);
	ft_putstr("\e[1;38;5;4m");
	ft_putnbr(size);
	ft_putstr("\e[1;38;5;9m");
	ft_putnbr(len);
	ft_putstr("\e[0m");	
	if (size == 0)
		return (malloc(16));
	// else
	// 	return (alloc(size, len, pagesize));
	if (!zone)
	{
		ft_putnbr(len * pagesize);
		ft_putchar('\n');
		if ((zone = mmap(0, len * pagesize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
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
		if ((ptr = mmap(0, len * pagesize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
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


// void		*alloc(size_t size, size_t len, int pagesize)
// {
// 	void *ptr;
// 	t_zone *zone;
// 	if ((ptr = mmap(NULL, len * pagesize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
// 		return (NULL);
// 	if (!g_zone)
// 	{
// 		zone = ptr;
// 		g_zone = zone;
// 	}
// 	else
// 	{
// 		while (zone->next)
// 			zone = zone->next;
// 		zone->next = ptr;
// 		zone = zone->next;
// 	}
// 	zone->size = size;
// 	zone->free = 0;
// 	zone->ptr = zone + sizeof(t_zone);
// 	zone->next = NULL;
// 	ft_putptr(zone->ptr);
// 	write(1, " DONE\n", 6);
// 	return (zone->ptr);
// }

int		main(void)
{
	int i = 0;
	int j = 0;
	void *ptr1;
	void *ptr2;

	while (i < 2) {
		ptr1 = malloc(16);
		memset(ptr1, 'A', 4095);
		ft_putstr(ptr1);
		free(ptr1);
		i++;
	}
	return (0);
}