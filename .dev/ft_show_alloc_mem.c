#include "ft_malloc.h"

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