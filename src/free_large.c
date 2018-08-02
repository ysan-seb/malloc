#include "malloc.h"

void		free_large(t_zone *zone, void *ptr)
{
	t_zone *tmp;
	int pagesize;
	size_t len;

	pagesize = getpagesize();
	if (zone->ptr == ptr)
	{
		g_zones.large = zone->next;
		len = (zone->size + sizeof(t_zone) - 1) / pagesize + 1;		
		if ((munmap(zone, len * pagesize)) == -1)
			perror("error: ");// write(1, "Free Error\n", 11);
	}
	else
	{
		while (zone->next)
		{
			if (zone->next->ptr == ptr)
			{
				tmp = zone->next->next;
				len = (zone->next->size + sizeof(t_zone) - 1) / pagesize + 1;
				if ((munmap(zone->next, len * pagesize)) == -1)
					perror("error: ");// write(1, "Free Error\n", 11);
				zone->next = tmp;
				break;
			}
			zone = zone->next;
		}
	}
}