#include "malloc.h"

void		free_tiny(t_zone *zone, void *ptr)
{
	// write(1,"FREE   ", 7);
	// ft_putptr(ptr);
	// ft_putchar('\n');


	// // t_zone *tmp;
	// int pagesize;
	// // size_t len;
	// pagesize = getpagesize();
	// if (zone->ptr == ptr)
	// {
	// 	// g_zones.tiny = zone->next;
	// 	// len = (zone->size + sizeof(t_zone) - 1) / pagesize + 1;		
	// 	// if ((munmap(zone, len * pagesize)) == -1)
	// 	// 	perror("error: ");// write(1, "Free Error\n", 11);
	// 	zone->free = 1;
	// }
	// else
	// {
	// 	while (zone->next)
	// 	{
	// 		if (zone->next->ptr == ptr)
	// 		{
	// 			zone->next->free = 1;
	// 			// tmp = zone->next->next;
	// 			// len = (zone->next->size + sizeof(t_zone) - 1) / pagesize + 1;
	// 			// if ((munmap(zone->next, len * pagesize)) == -1)
	// 			// 	perror("error: ");// write(1, "Free Error\n", 11);
	// 			// zone->next = tmp;
	// 			break;
	// 		}
	// 		zone = zone->next;
	// 	}
	// }

	zone->free = 1;
}