#include "ft_malloc.h"

void		ft_free(void *ptr)
{
	t_zone	*tmp;
	t_zone	*zone;

	if (!(zone = g_zone))
		return;
	if (zone->ptr == ptr)
	{
		tmp = zone->next;
		if ((munmap(zone, ((zone->size - 1) + sizeof(t_zone) / getpagesize() + 1) * getpagesize())) == -1)
			printf("[0] Free error\n");
		g_zone = tmp;
	}
	else
	{
		while(zone->next)
		{
			if (zone->next->ptr == ptr)
			{
				tmp = zone->next->next;
				if ((munmap(zone->next, ((zone->next->size - 1) + sizeof(t_zone) / getpagesize() + 1) * getpagesize())) == -1)
					printf("[1] Free error\n");
				zone->next = tmp;
			}
			zone = (zone->next) ? zone->next : zone;
		}
	}
}

void		*ft_malloc(size_t size)
{
	int		len;
	void	*ptr;
	t_zone	*zone;

	len = ((size - 1) + sizeof(t_zone)) / getpagesize() + 1;
	zone = g_zone;
	if (!zone)
	{
		if ((g_zone = mmap(NULL, len * getpagesize(), PROT_READ
			| PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
			return (NULL);
		g_zone->ptr = g_zone + sizeof(t_zone);
		g_zone->size = size;
		g_zone->next = NULL;
		return (g_zone->ptr);
	}
	else
	{
		if ((ptr = mmap(NULL, len * getpagesize(), PROT_READ
			| PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
			return (NULL);
		while (zone->next)
			zone = zone->next;
		zone->next = ptr;
		zone = zone->next;
		zone->ptr = zone + sizeof(t_zone);
		zone->size = size;
		zone->next = NULL;
		return (zone->ptr);
	}
}

void		show_alloc_mem(void)
{
	int		i;
	t_zone *zone;

	i = 0;
	zone = g_zone;
	printf("LARGE:\n");
	if (!zone)
		printf("Empty\n");
	while (zone)
	{
		printf("[%d] %p\n", i, zone);
		zone = zone->next;
		i++;
	}
}

int			main(void)
{
	void	*ptr_1;
	void	*ptr_2;
	void	*ptr_3;
	void	*ptr_4;
	void	*ptr_5;

	ptr_1 = ft_malloc(1);
	ptr_2 = ft_malloc(1);
	ptr_3 = ft_malloc(1);
	ptr_4 = ft_malloc(1);
	ptr_5 = ft_malloc(1);
	show_alloc_mem();
	ft_free(ptr_5);
	show_alloc_mem();
	ft_free(ptr_4);
	show_alloc_mem();
	ft_free(ptr_3);
	show_alloc_mem();
	ft_free(ptr_2);
	show_alloc_mem();
	ft_free(ptr_1);
	show_alloc_mem();
	return (0);
}
