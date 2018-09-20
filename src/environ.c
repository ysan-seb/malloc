#include "malloc.h"

static int			ft_strcmp(char *s1, char *s2)
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

void	check_var_env(void)
{
	int 		i;
	extern char **environ;

	i = 0;
	while (environ[i])
	{
		if (ft_strcmp("MALLOC_VERBOSE", environ[i]) == 0)
			g_zones.v = 1;
		if (ft_strcmp("MALLOC_VERBOSITY_COLOR", environ[i]) == 0)
			g_zones.v_color = 1;
		i++;
	}
    g_zones.checked = 1;
}