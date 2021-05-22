#include "minishell.h"

void     ft_echo(t_cmd *cmd)
{
    if (ft_strchr(cmd->flags, 'n'))
        write(1, cmd->args[0], ft_strlen(cmd->args[0]));
    else
        printf("%s\n", cmd->args[0]);
}

void    ft_pwd(void)
{
    int     size;
    char    *tmp;

    size = 1024;
    tmp = malloc(size);
    getcwd(tmp, size);
    while (tmp == NULL)
    {
        ft_realloc(tmp, size);
        size += size;
        getcwd(tmp, size);
    }
    printf("%s\n", tmp);
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

int     ft_arrsize(char **str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void    ft_arrfree(char **arr)
{
    int     i;

    i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}

char    **ft_arraddstr(char **arr, char *str, int pos)
{
    int     i;
    int     size;
    char    **tmp;
    char    **old;

    i = 0;
    size = ft_arrsize(arr);
    if (pos > size)
        return (0);
    tmp = (char **)malloc(sizeof(arr) * (size + 1));
    while (i < pos)
    {
        tmp[i] = malloc(ft_strlen(arr[i]) + 1);
        ft_strcpy(tmp[i], arr[i]);
        i++;
    }
    tmp[i] = malloc(ft_strlen(str) + 1);
    ft_strcpy(tmp[i++], str);
    while (i < size)
    {
        tmp[i] = malloc(ft_strlen(arr[i - 1]) + 1);
        ft_strcpy(tmp[i], arr[i - 1]);
        i++;
    }
    tmp[i] = NULL;
    old = arr;
    arr = tmp;
//    ft_arrfree(old);
    int k = 0;
    while (arr[k])
        printf("%s\n", arr[k++]);
    return (arr);
}

char    **ft_arrcpy(char **dest, char **arr)
{
    int     i;

    i = 0;
    while (arr[i])
    {
        dest[i] = malloc(ft_strlen(arr[i]) + 1);
        ft_strcpy(dest[i], arr[i]);
        i++;
    }
    dest[i] = NULL;
    return(dest);
}

void    ft_export(t_cmd *cmd, char **envp)
{
    char    **tmp;
    int     size;

    if (!cmd->args[0])
    {
        size = ft_arrsize(envp);
        tmp = (char **)malloc(sizeof(envp) * (size + 1));
        ft_arrcpy(tmp, envp);
        ft_qsort_s(tmp, 0, ft_arrsize(tmp) - 1);
        size = 0;
        while (tmp[size])
            printf("%s\n", tmp[size++]);
    }
    else
        ft_arraddstr(envp, cmd->args[0], ft_arrsize(envp));
}

void    processor(t_cmd *cmd, char **envp)
{
    if (!ft_strcmp(cmd->type, "echo"))
        ft_echo(cmd);
    if (!ft_strcmp(cmd->type, "pwd"))
        ft_pwd();
    if (!ft_strcmp(cmd->type, "cd"))
        ft_cd(cmd);
    if (!ft_strcmp(cmd->type, "env"))
        ft_env(envp);
    if (!ft_strcmp(cmd->type, "export"))
        ft_export(cmd, envp);
    if (!ft_strcmp(cmd->type, "exit"))
        ft_exit();
}