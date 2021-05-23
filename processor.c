#include "minishell.h"

void     ft_echo(t_builtins *func)
{
    if (ft_strchr(func->flags, 'n'))
        write(1, func->args[0], ft_strlen(func->args[0]));
    else
        printf("%s\n", func->args[0]);
}

void    ft_pwd(t_builtins *func)
{
    int     size;
    char    *tmp;

    size = 1024;
    if (func->args[0] != 0)
        printf("pwd: too many arguments\n");
    else
    {
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
}

void    ft_exit(void)
{
    printf("exit\n");
    exit(0);
}

void    ft_cd(t_builtins *func)
{
    if (func->args[0] == 0)
        chdir("/Users");
    else if (chdir(func->args[0]) == -1)
        printf("cd: no such file or directory: %s\n", func->args[0]);
}

void    ft_env(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
        printf("%s\n", envp[i++]);
}

void    processor(t_builtins *func, char **envp)
{
    if (!ft_strcmp(func->type, "echo"))
        ft_echo(func);
    if (!ft_strcmp(func->type, "pwd"))
        ft_pwd(func);
    if (!ft_strcmp(func->type, "cd"))
        ft_cd(func);
    if (!ft_strcmp(func->type, "env"))
        ft_env(envp);
    if (!ft_strcmp(func->type, "exit"))
        ft_exit();
}