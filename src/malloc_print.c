#include "malloc.h"

void    malloc_print(char *function, size_t size, void *ptr)
{
    ft_putstr(function);
    write(1, " ", 1);
    if (g_zones.v_color)
    {
        if (size <= TINY)
            ft_putstr("\e[1;38;5;2m");
        else if (size > TINY && size <= SMALL)
            ft_putstr("\e[1;38;5;3m");        
        else
            ft_putstr("\e[1;38;5;1m");            
    }
    ft_putnbr(size);
    ft_putstr("\e[0m bytes at ");
    if (g_zones.v_color)
        ft_putstr("\e[1;38;5;4m0x");
    ft_itoa_base((unsigned long long)ptr, 16);
    ft_putstr("\e[0m");        
    write(1, "\n", 1);
}