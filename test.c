#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void			*check(void *t)
{
	void 		*ptr;

	ptr = malloc(70);
	ptr = realloc(ptr, 100);
	free(ptr);
	ptr = calloc(10, 42);
	return (ptr);
}

int 			main(void)
{
	int 		i;
	pthread_t	thread[4];

	pthread_create(&thread[0], NULL, check, NULL);
	pthread_create(&thread[1], NULL, check, NULL);
	pthread_create(&thread[2], NULL, check, NULL);
	pthread_create(&thread[3], NULL, check, NULL);
	i = 0;
	while (i < 4)
	{
		write(1, "OK\n", 3);
		pthread_join(thread[i], NULL);
		i++;
	}
	return 0;
}
