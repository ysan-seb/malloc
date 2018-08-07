#include "malloc.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = b;
	i = 0;
	while (i < len)
	{
		ptr[i] = c;
		i++;
	}
	return (b);
}

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
