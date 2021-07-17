#include "../includes/minishell.h"

char	**get_dir_content(char *str)
{
    DIR				*dir;
    struct dirent	*entry;
	char			**names;

	names = malloc(sizeof(char *));
	names[0] = NULL;
    dir = opendir(str);
    if (!dir) {
        perror("diropen");
        exit(1);
    };
	int i = 0;
    while ( (entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			names = ft_arradd_str(names, entry->d_name, i);
			if (entry->d_type == 4)
				names[i] = ft_strjoin(names[i], "/");
			i++;
		}
    }
	free(str);
    closedir(dir);
	return (names);
}
