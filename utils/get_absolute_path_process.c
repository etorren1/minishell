#include "../includes/minishell.h"

char	*get_absolute_path_process(char *name)
{
	char	*str;
	int		i;

	str = NULL;
	if (!ft_strncmp(name, "/Users", 6))
		str = ft_strdup(name);
	else
	{
		str = get_pwd();
		str = ft_strjoin(str, "/");
		str = ft_strjoin(str, name);
	}
	i = ft_strlen(str);
	while (str[i] != '/')
		str[i--] = 0;
	if (str[i - 1] == '.')
	{
		str[i] = 0;
		str[i - 1] = 0;
	}
	return (str);
}
