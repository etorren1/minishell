#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct  s_cmd {
    char        *type;
    char        *flags;
    char        **args;
    int         count_args;
	int			len;
}               t_cmd;

#endif
