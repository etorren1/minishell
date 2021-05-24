#include "../includes/minishell.h"

int	find_environment(char *env, char **envp)
{
	char	*str;
	int		i;
	int		len;

	len = 0;
	while (env[len] != '=' && env[len])
        len++;
	i = -1;
	while (envp[++i])
		if (!ft_strncmp(env, envp[i], len) && envp[i][len] == '=')
			return (i);
	return (-1);
}