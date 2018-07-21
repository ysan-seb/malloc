/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 10:34:28 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/07/21 16:10:46 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct		s_zone
{
	size_t			size;
	struct s_zone	*next;
}					t_zone;

typedef struct		s_tsl
{
	t_zone			*lzone;
}					t_tsl;

t_tsl				g_tsl;

void				*ft_malloc(size_t size)
{
	void	*ptr;
	t_tsl	tsl;
	size_t	len;

	tsl = g_tsl;
	if (size > 0)
	{
		len = ((size - 1) + sizeof(t_tsl)) / getpagesize() + 1;
		if (!g_tsl.lzone)
		{
			if ((g_tsl.lzone = mmap(NULL, len * getpagesize(), PROT_READ
			| PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
				return (NULL);
			g_tsl.lzone->size = len;
			return (g_tsl.lzone + sizeof(t_tsl));
		}
		else
		{
			if ((ptr = mmap(NULL, len * getpagesize(), PROT_READ
			| PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
				return (NULL);
			while (tsl.lzone->next)
				tsl.lzone = tsl.lzone->next;
			tsl.lzone->next = ptr;
			tsl.lzone = tsl.lzone->next;
			tsl.lzone->size = len;
			tsl.lzone->next = NULL;
			return (tsl.lzone + sizeof(t_tsl));
		}
	}
	return (NULL);
}

void				ft_free(void *ptr)
{
	int	ret;

	// ret = munmap(ptr, size * getpagesize());
	printf("ret = %d\n", ret);
}

void				ft_show_alloc_mem(void)
{
	int		i;
	t_tsl	tsl;

	i = 0;
	tsl = g_tsl;
	printf("\n");
	while (tsl.lzone->next)
	{
		printf("zone[%d]\nAdress : %p\nPtr : %p\nSize : %zu\n\n",
				i, tsl.lzone, tsl.lzone + sizeof(t_tsl), tsl.lzone->size);
		tsl.lzone = tsl.lzone->next;
		i++;
	}
	printf("zone[%d]\nAdress : %p\nPtr : %p\nSize : %zu\n",
			i, tsl.lzone, tsl.lzone + sizeof(t_tsl), tsl.lzone->size);
}

int					main(int ac, char **av)
{
	int		i;
	char	*ptr;

	i = 0;
	if (ac < 2)
		return (-1);
	else
	{
		ptr = (char *)ft_malloc(sizeof(char) * strlen(av[1]));
		ptr = (char *)ft_malloc(sizeof(char) * strlen(av[1]));
		ptr = (char *)ft_malloc(sizeof(char) * strlen(av[1]));
		ptr = (char *)ft_malloc(sizeof(char) * strlen(av[1]));
		ptr = (char *)ft_malloc(sizeof(char) * strlen(av[1]));
		ft_show_alloc_mem();
	}
	return (0);
}
