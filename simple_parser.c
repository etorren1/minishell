#include "minishell.h"

int     end_command(char ch)
{
    if (ch != '\0' && ch != '\n' && ch != ';' && ch != '|')
        return (0);
    return (1);
}

int    simple_parser(char *str, t_cmd *cmd)
{
    int     i;
    int     j;

    i = 0;
    j = 0;
    cmd->flags = NULL;
    cmd->args = malloc(3);
    cmd->count_args = 1;
    cmd->len = 0;
    cmd->args[0] = malloc(1024);
    cmd->args[1] = NULL;
    cmd->args[2] = NULL;
    while (str[i] == ' ' && !end_command(str[i]))
        i++;
    while (str[i] != ' ' && !end_command(str[i]))
        cmd->args[0][j++] = str[i++];
    cmd->args[0][j] = '\0';
    j = 0;
    while (str[i] == ' ' && !end_command(str[i]))
        i++;
    if (str[i] == '-')
    {
        cmd->flags = malloc(1024);
        while (str[i] != ' ' && !end_command(str[i]))
            cmd->flags[j++] = str[i++];
        cmd->flags[j] = '\0';
    }
    while (str[i] == ' ' && !end_command(str[i]))
        i++;
    int k = 1;
    while (!end_command(str[i]))
    {
        j = 0;
        cmd->args[k] = malloc(1024);
        if (!ft_strcmp(cmd->args[0], "echo"))
            while (!end_command(str[i]))
                cmd->args[k][j++] = str[i++];
        else
            while (str[i] != ' ' && !end_command(str[i]))
                cmd->args[k][j++] = str[i++];
        k++;
        cmd->count_args++;
    }
    cmd->len = i;
    i++;
    if (str[i])
        return(1);
    i = 0;
    return (0);
}