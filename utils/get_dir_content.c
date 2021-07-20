#include "../includes/minishell.h"

static char	**write_names(DIR *dir)
{
	struct dirent	*entry;
	char			**names;
	int				i;

	i = 0;
	names = malloc(sizeof(char *));
	names[0] = NULL;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			names = ft_arradd_str(names, entry->d_name, i);
			if (entry->d_type == 4)
				names[i] = ft_strjoin(names[i], "/");
			i++;
		}
		entry = readdir(dir);
	}
	return (names);
}

char	**get_dir_content(char *str)
{
	DIR				*dir;
	char			**names;

	dir = opendir(str);
	if (!dir)
	{
		perror("diropen");
		exit(1);
	}
	names = write_names(dir);
	free(str);
	closedir(dir);
	return (names);
}
