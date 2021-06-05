#include "../includes/minishell.h"

char	*get_pwd(void)
{
	int 	size;
	char	*pwd;

	size = 128;
	pwd = NULL;
	pwd = getcwd(pwd, size);
	while (errno == 34)
	{
		size += size;
		errno = 0;
		free(pwd);
		pwd = getcwd(pwd, size);
	}
	return (pwd);
}