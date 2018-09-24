#include "inc/malloc.h"

int	main(void)
{
	int i;
	void	*ptr1, *ptr2;
	i = 0;
	while (i < 6)
	{
		ptr1 = malloc(16);
		ptr2 = reallocf(ptr1, 32);
		i++;
	}
	show_alloc_mem();
	show_graph_mem();
	return (0);
}
