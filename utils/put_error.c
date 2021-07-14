#include "../includes/minishell.h"

void    put_error(char *prefix, char *cmd, char *args, char *err)
{
    char    *output;

    if (prefix)
    {
        output = ft_strdup(prefix);
        output = ft_strjoin(output, cmd);
    }
    else
        output = ft_strdup(cmd);
    output = ft_strjoin(output, ": ");
    if (args)
    {
        output = ft_strjoin(output, args);
        output = ft_strjoin(output, ": ");
    }
    output = ft_strjoin(output, err);
    ft_putendl_fd(output, 2);
    free(output);
}
