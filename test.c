#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	printf("%s\n", memset(malloc(3312), 'A', 4096));
	return (0);
}
