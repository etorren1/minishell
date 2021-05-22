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
    cmd->type = malloc(1024);
    cmd->flags = malloc(1024);
    cmd->flags[0] = '\0';
    cmd->args = malloc(4);
    cmd->count_args = 0;
    cmd->len = 0;
    cmd->args[0] = NULL;
    while (str[i] == ' ' && !end_command(str[i]))
        i++;
    while (str[i] != ' ' && !end_command(str[i]))
        cmd->type[j++] = str[i++];
    j = 0;
    cmd->type[i] = '\0';
    while (str[i] == ' ' && !end_command(str[i]))
        i++;
    if (str[i] == '-')
    {
        i++;
        while (str[i] != ' ' && !end_command(str[i]))
            cmd->flags[j++] = str[i++];
        cmd->flags[j] = '\0';
    }
    while (str[i] == ' ' && !end_command(str[i]))
        i++;
    int k = 0;
    while (!end_command(str[i]))
    {
        j = 0;
        cmd->args[k] = malloc(1024);
        if (!ft_strcmp(cmd->type, "echo"))
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
    return (0);
}