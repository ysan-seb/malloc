#include "ft_malloc.h"

void copy_block(t_zone *src , t_zone *dst)
{
	int *sdata ,* ddata;
	size_t i;

	i = 0;
	sdata = src->ptr;
	ddata = dst->ptr;
	// for (i=0; i*4<src->size && i*4<dst->size; i++)
	// 	ddata[i] = sdata[i];
	while(i * 4 < src->size && i * 4 < dst->size)
	{
		ddata[i] = sdata[i];
		i++;
	}
}

int     ft_need_space(size_t size1, size_t size2)
{
    size_t origin;
    size_t asked;
    
	origin = ((size1 - 1) + sizeof(t_zone)) / getpagesize() + 1;
    asked = ((size1 + size2 - 1) + sizeof(t_zone)) / getpagesize() + 1;
    if (origin == asked || origin > asked)
        return (0);
    else
        return (1);
}

void    *ft_realloc(void *ptr, size_t size)
{
	size_t	len;
    t_zone	*tmp;
	t_zone	*zone;
	t_zone	*new_zone;

	if (!(zone = g_zone))
		return (NULL);
	if (zone->ptr == ptr)
	{
        if (ft_need_space(zone->size, size))
		{
			tmp = zone->next;
			len = ((zone->size + size - 1) + sizeof(t_zone)) / getpagesize() + 1;
			if ((new_zone = mmap(NULL, len * getpagesize(), PROT_READ
			| PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
			{
				printf("Realloc error\n");
				return (NULL);
			}
			new_zone->ptr = new_zone + 32;
			new_zone->size = zone->size + size;
			copy_block(zone , new_zone);
            //ft_memcpy(new_zone + 32, zone + 32, size);
			// if ((munmap(zone, ((zone->size - 1) + sizeof(t_zone) / getpagesize() + 1) * getpagesize())) == -1)
			// 	printf("[0] Free error\n");
			new_zone->next = tmp;
			g_zone = new_zone;
			return (new_zone->ptr);
		}
        else
		
            return(zone->ptr);
	}
	else
	{
		while(zone->next)
		{
			if (zone->next->ptr == ptr)
			{
                if (ft_need_space(zone->size, size))
                {
					tmp = zone->next->next;
					len = ((zone->size + size - 1) + sizeof(t_zone)) / getpagesize() + 1;
					if ((new_zone = mmap(NULL, len * getpagesize(), PROT_READ
					| PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
						return (NULL);
					zone->next = new_zone;
					new_zone->next = tmp;
					new_zone->size = zone->size + size;
					copy_block(zone , new_zone);
					// if ((munmap(zone, ((zone->size - 1) + sizeof(t_zone) / getpagesize() + 1) * getpagesize())) == -1)
					// 	printf("[0] Free error\n");
					new_zone->ptr = new_zone + sizeof(t_zone);
					return (new_zone->ptr);
				}
                else
                    return (zone->next->ptr);
				zone->next = tmp;
			}
			zone = (zone->next) ? zone->next : zone;
		}
	}
    return (NULL);
}