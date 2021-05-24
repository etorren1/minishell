#include "../includes/minishell.h"

char	*get_absolute_path_process(char *proc)
{
	char	*str;
	int		size;
	int		i;

	size = 1024;
	while (!(str = getcwd(str, size))) // maybe use ERRNO ???
		size += size;
	str = ft_strjoin(str, "/");
	str = ft_strjoin(str, proc);
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