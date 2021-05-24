#include "../includes/minishell.h"

char	*get_absolute_path_process(char **envp)
{
	char	*str;
	int		ret;
	int		i;

	ret = find_environment("PWD", envp);
	str = ft_substr(envp[ret], 4, ft_strlen(envp[ret]) - 4);
	str = ft_strjoin(str, "/");
	ret = find_environment("_", envp);
	str = ft_strjoin(str, &envp[ret][2]);
	i = ft_strlen(str);
	while (str[i] != '/')
		str[i--] = 0;
	if (str[i - 1] == '.')
	{
		str[i] = 0;
		str[i - 1] = 0;
	}
	return(str);
}