#include "ft_malloc.h"
#include <string.h>

#define M (1024 * 1024) 

void print(char *s) 
{ 
	write(1, s, strlen(s)); 
} 

int		test1(void)
{
	int i; 
	char *addr; 

	i = 0; 
	while (i < 1024) 
	{ 
		i++; 
	} 
	return (0); 
}

int		test2(void)
{ 
	int i; 
	char *addr; 

	i = 0; 
	while (i < 1024) 
	{ 
		addr = (char*)ft_malloc(1024); 
		addr[0] = 42; 
		i++; 
	} 
	return (0); 
} 

int		test3(void)
{ 
	int i; 
	char *addr; 

	i = 0; 
	while (i < 1024) 
	{ 
		addr = (char*)ft_malloc(1024); 
		addr[0] = 42; 
		ft_free(addr); 
		i++; 
	} 
	return (0); 
}

int		test4(void)
{ 
	char *addr1; 
	char *addr3; 

	addr1 = (char*)ft_malloc(16*M); 
	strcpy(addr1, "Bonjours\n"); 
	print(addr1); 
	addr3 = (char*)ft_realloc(addr1, 128*M); 
	addr3[127*M] = 42; 
	print(addr3); 
	return (0); 
} 

int		test5(void)
{ 
	char *addr1; 
	char *addr2; 
	char *addr3; 

	addr1 = (char*)ft_malloc(16*M); 
	strcpy(addr1, "Bonjours\n"); 
	print(addr1); 
	addr2 = (char*)ft_malloc(16*M); 
	addr3 = (char*)ft_realloc(addr1, 128*M); 
	addr3[127*M] = 42; 
	print(addr3); 
	return (0); 
} 

int		test6()
{ 
	char *addr; 

	addr = ft_malloc(16); 
	ft_free(NULL); 
	ft_free((void *)addr + 5); 
	if (ft_realloc((void *)addr + 5, 10) == NULL) 
		print("Bonjours\n");
	return (0);
}

int		test7()
{ 
	ft_malloc(1024); 
	ft_malloc(1024 * 32); 
	ft_malloc(1024 * 1024); 
	ft_malloc(1024 * 1024 * 16); 
	ft_malloc(1024 * 1024 * 128); 
	show_alloc_mem(); 
	return (0); 
} 

int		main(int ac, char **av)
{
	if (ac > 1)
	{
		if (av[1][0] == '1')
			test1();
		else if (av[1][0] == '2')
			test2();
		else if (av[1][0] == '3')
			test3();
		else if (av[1][0] == '4')
			test4();
		else if (av[1][0] == '5')
			test5();
		else if (av[1][0] == '6')
			test6();
		else if (av[1][0] == '7')
			test7();
	}
	// else
	// {
	// 	test1();
	// 	test2();
	// 	test3();
	// 	test4();
	// 	test5();
	// 	test6();
	// 	test7();
	// }
	return (0);
}
// int			main(void)
// {
// 	void	*ptr_1;
// 	void	*ptr_2;
// 	void	*ptr_3;
// 	void	*ptr_4;
// 	void	*ptr_5;

// 	ptr_1 = ft_malloc(1);
// 	ptr_2 = ft_malloc(1);
// 	ptr_3 = ft_malloc(1);
// 	ptr_4 = ft_malloc(1);
// 	ptr_5 = ft_malloc(1);
// 	show_alloc_mem();
// 	ptr_3 = ft_realloc(ptr_3, 10000);    
// 	show_alloc_mem();
// 	ft_free(ptr_5);
// 	show_alloc_mem();
// 	ft_free(ptr_4);
// 	show_alloc_mem();
// 	ft_free(ptr_3);
// 	show_alloc_mem();
// 	ft_free(ptr_2);
// 	show_alloc_mem();
// 	ft_free(ptr_1);
// 	show_alloc_mem();
// 	return (0);
// }
