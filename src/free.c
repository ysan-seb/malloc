#include "malloc.h"

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}


void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		ft_putstr("-2147483648");
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar(n + '0');
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*dest;
	const char	*source;

	i = 0;
	dest = dst;
	source = src;
	while (i < n)
	{
		dest[i] = source[i];
		i++;
	}
	return (dest);
}

void		ft_putptr(void *ptr)
{
	size_t	n;
	size_t	i;
	char	c;
	int		color;

	n = (size_t)ptr;
	color = 0;
	write(1, "0x", 2);
	i = 1L << 60;
	while (i)
	{
		c = n / i > 9 ? n / i + 'A' - 10 : n / i + '0';
		n = n - n / i * i;
		if (c > '0')
			color = 1;
		if (color == 1)
			ft_putstr("\e[1;38;5;4m");
		write(1, &c, 1);
		i /= 16;
	}
	ft_putstr("\e[0m");
}

static int	check_pointer(void *ptr)
{
	t_zone *zone;

	zone = g_zone;
	if (!zone)
		return (0);
	else
	{
		while (zone)
		{
			if (zone->ptr == ptr)
				return (1);
			zone = zone->next;
		}
	}
	return (0);
}

void		free(void *ptr)
{
	t_zone *tmp;
	t_zone *zone = NULL;
	int pagesize;
	size_t len;
	int ret = 0;

	zone = g_zone;
	pagesize = getpagesize();
	// write(1, "FREE    : ", 10);
	// ft_putptr(ptr);	
	if (!ptr)
	{
		// write(1, "\n", 1);
		return;
	}
	if (!check_pointer(ptr))
	{
		// write(1, " UNKNOWN\n", 10);
		return;
	}
	if (zone->ptr == ptr)
	{
		g_zone = zone->next;
		len = (zone->size + sizeof(t_zone) - 1) / pagesize + 1;		
		// ft_putstr("\e[1;38;5;9m");
		// ft_putnbr(zone->size);
		// ft_putstr("\e[1;38;5;4m");
		// ft_putnbr(len);
		// ft_putstr("\e[0m");
		if ((munmap(zone, len * pagesize)) == -1)
			perror("error: ");// write(1, "Free Error\n", 11);
	}
	else
	{
		while (zone->next)
		{
			if (zone->next->ptr == ptr)
			{
				tmp = zone->next->next;
				len = (zone->next->size + sizeof(t_zone) - 1) / pagesize + 1;
				// ft_putstr("\e[1;38;5;9m");
				// ft_putnbr(zone->next->size);
				// ft_putstr("\e[1;38;5;4m");
				// ft_putnbr(len);
				// ft_putstr("\e[0m");
				if ((munmap(zone->next, len * pagesize)) == -1)
					perror("error: ");// write(1, "Free Error\n", 11);
				zone->next = tmp;
				break;
			}
			zone = zone->next;
		}
	}
	// write(1, " DONE\n", 7);
	// show_alloc_mem();
}