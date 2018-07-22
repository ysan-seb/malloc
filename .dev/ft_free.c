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