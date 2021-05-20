#include "minishell.h"

void     ft_echo(t_cmd *cmd)
{
    if (ft_strchr(cmd->flags, 'n'))
        write(1, cmd->args[0], ft_strlen(cmd->args[0]));
    else
        printf("%s\n", cmd->args[0]);
}

void    ft_pwd(t_cmd *cmd)
{
    int     size;
    char    *tmp;

    if (cmd->args[0] != 0)
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

void    ft_cd(t_cmd *cmd)
{
    if (cmd->args[0] == 0)
        chdir("/Users");
    else if (chdir(cmd->args[0]) == -1)
        printf("cd: no such file or directory: %s\n", cmd->args[0]);
}

void    ft_env(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
        printf("%s\n", envp[i++]);
}

void    processor(t_cmd *cmd, char **envp)
{
    if (!ft_strcmp(cmd->type, "echo"))
        ft_echo(cmd);
    if (!ft_strcmp(cmd->type, "pwd"))
        ft_pwd(cmd);
    if (!ft_strcmp(cmd->type, "cd"))
        ft_cd(cmd);
    if (!ft_strcmp(cmd->type, "env"))
        ft_env(envp);
    if (!ft_strcmp(cmd->type, "exit"))
        ft_exit();
}