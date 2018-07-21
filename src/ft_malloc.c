/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 10:34:28 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/07/14 16:58:10 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct      s_zone
{
    size_t          size;
    int             free;
    struct s_zone   *next;
}                   t_zone;

typedef struct      s_tsl
{
    t_zone          *lzone;
}                   t_tsl;

t_tsl              g_tsl;

void                *ft_malloc(size_t size)
{
    int i = 0;
	void *ptr;
    t_tsl tsl = g_tsl;
	size_t len;


	if (size == 0)
		return (NULL);	
	len = (size - 1) + sizeof(t_zone) / getpagesize() + 1;
    if ((ptr = mmap(NULL, len * getpagesize(), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
        return (NULL);
    printf("ptr tsl = %p\n", tsl.zone);
    if (!tsl.lzone) {
        tsl.lzone = ptr;
        printf("tsl = %p\n", tsl.lzone);    
        tsl.lzone->size = size;
        tsl.lzone->free = 1;
        tsl.lzone->next = NULL;
        printf("tsl = %p\n", ptr);
    } else {
        while (tsl.lzone->next)
        {
            tsl.lzone = tsl.lzone->next;
            i++;
        }
        printf("%d\n", i);
        tsl.lzone = ptr;
        printf("ptr = %p\n", ptr);
        printf("new ptr = %p\n", tsl.lzone);
        printf("new ptr + 24 = %p\n", tsl.lzone + sizeof(t_tsl));
    }
	return (tsl.lzone + sizeof(t_tsl));
}

    // printf("ptr = %p\n", ptr);
    // printf("zone = %p\n", g_tsl.lzone);
    // printf("zone  + sizeof t_tsl = %p\n", g_tsl.lzone + sizeof(t_tsl));
    // printf("sizeof struct = %zu\n", sizeof(size_t));

void                ft_free(void *ptr)
{
    int ret;

    // ret = munmap(ptr, size * getpagesize());
    printf("ret = %d\n", ret);
}

int main(int ac, char **av)
{
    int i;
    char *ptr1;

    i = 0;
    if (ac < 2)
        return (-1);
    else
    {
        ptr1 = (char *)ft_malloc(sizeof(char) * strlen(av[1]));
        printf("str1 = %p\n", ptr1);
        ptr1 = strcpy(ptr1, av[1]);
        ptr1 = (char *)ft_malloc(sizeof(char) * strlen(av[1]));
        ptr1 = (char *)ft_malloc(sizeof(char) * strlen(av[1]));
        ptr1 = (char *)ft_malloc(sizeof(char) * strlen(av[1]));
        ptr1 = (char *)ft_malloc(sizeof(char) * strlen(av[1]));
        printf("str2 = %p\n", ptr1);
        ft_free(ptr1);
    }
    return (0);
}