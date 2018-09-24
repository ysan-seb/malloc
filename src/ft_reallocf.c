#include "malloc.h"

void    *ft_reallocf(void *ptr, size_t size)
{
    void    *new;

    if (!(new = ft_realloc(ptr, size)))
        free(ptr);
    return (new);
}