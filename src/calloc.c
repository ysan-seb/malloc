#include "malloc.h"

void    *calloc(size_t nmemb, size_t size)
{
	int		len;
	void	*ptr;
	t_zone	*zone;

	write(1, "CALLOC\n", 7);
	len = ((size * nmemb - 1) + sizeof(t_zone)) / getpagesize() + 1;
	zone = g_zone;
	if (!zone)
	{
		if ((g_zone = mmap(NULL, len * getpagesize(), PROT_READ
			| PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
			return (NULL);
		g_zone->ptr = g_zone + sizeof(t_zone);
		g_zone->size = size * nmemb;
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
		zone->size = size * nmemb;
		zone->next = NULL;
		return (zone->ptr);
	}
}
