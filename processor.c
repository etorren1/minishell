#include "includes/minishell.h"

void     ft_echo(t_builtins *func)
{
    if (ft_strchr(func->flags, 'n'))
        write(1, func->args[0], ft_strlen(func->args[0]));
    else
        printf("%s\n", func->args[0]);
}

void    ft_pwd(void)
{
    int     size;
    char    *tmp;

    tmp = malloc(size);
    getcwd(tmp, size);
    while (tmp == NULL)
    {
        size += size;
        ft_realloc(tmp, size);
        getcwd(tmp, size);
    }
    printf("%s\n", tmp);
}

void    ft_exit(void)
{
    printf("exit\n");
    exit(0);
}

void    processor(t_builtins *func)
{
    if (!ft_strcmp(func->type, "echo"))
        ft_echo(func);
    if (!ft_strcmp(func->type, "pwd"))
        ft_pwd();
    if (!ft_strcmp(func->type, "exit"))
        ft_exit();
}
