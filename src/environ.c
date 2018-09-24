/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 16:50:50 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/09/22 16:51:39 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int		ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	return (0);
}

void			check_var_env(void)
{
	int			i;
	extern char	**environ;

	i = 0;
	while (environ[i])
	{
		if (ft_strcmp("MALLOC_VERBOSE", environ[i]) == 0)
			g_zones.v = 1;
		if (ft_strcmp("MALLOC_VERBOSITY_COLOR", environ[i]) == 0)
			g_zones.v_color = 1;
		if (ft_strcmp("MALLOC_SHOW_MEM_COLOR", environ[i]) == 0)
			g_zones.s_color = 1;
		i++;
	}
	g_zones.checked = 1;
}
