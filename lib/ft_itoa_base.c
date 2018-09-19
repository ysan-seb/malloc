/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:55:33 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/09/18 16:05:56 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int			nb_len_base(unsigned long long value, int base)
{
	int		len;
	double	pow;

	len = 0;
	pow = 1;
	if (value < 0 && base == 10)
		len++;
	(value < 0) ? value = -value : 0;
	while (value >= (pow *= base))
		len++;
	return (len + 1);
}

void				ft_itoa_base(unsigned long long value, int base)
{
	char	s[13];
	int		len;

	if (base < 2 || base > 16)
		return ;
	len = nb_len_base(value, base);
	s[len] = '\0';
	if (value < 0 && base == 10)
		s[0] = '-';
	(value < 0) ? value = -value : 0;
	if (value == 0)
	{
		s[0] = '0';
		s[1] = '\0';
		ft_putstr(s);
	}
	while (value)
	{
		s[--len] = (value % base > 9) ? value % base - 10 + 'a'
			: value % base + '0';
		value /= base;
	}
	ft_putstr(s);
}
