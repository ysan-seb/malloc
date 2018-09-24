#include "malloc.h"

void    *reallocf(void *ptr, size_t size)
{
    void    *new_ptr;

    if (pthread_mutex_lock(&g_lock) != 0)
		return (NULL);
	if (!g_zones.checked)
		check_var_env();
    new_ptr = ft_reallocf(ptr, size);
    if (g_zones.v)
		malloc_print("REALLOCF", align(size), new_ptr);
	if (pthread_mutex_unlock(&g_lock) != 0)
		return (NULL);
    return (new_ptr);
}