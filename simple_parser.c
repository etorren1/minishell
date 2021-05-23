#include "minishell.h"

int     end_command(char ch)
{
    if (ch != '\0' && ch != '\n' && ch != ';' && ch != '|')
        return (0);
    return (1);
}

int    simple_parser(char *str, t_builtins *funct)
{
    int     i;
    int     j;

    i = 0;
    j = 0;
    funct->type = malloc(1024);
    funct->flags = malloc(1024);
    funct->flags[0] = '\0';
    funct->args = malloc(4);
    funct->count_args = 0;
    funct->len = 0;
    funct->args[0] = NULL;
    while (str[i] == ' ' && !end_command(str[i]))
        i++;
    while (str[i] != ' ' && !end_command(str[i]))
        funct->type[j++] = str[i++];
    j = 0;
    funct->type[i] = '\0';
    while (str[i] == ' ' && !end_command(str[i]))
        i++;
    if (str[i] == '-')
    {
        i++;
        while (str[i] != ' ' && !end_command(str[i]))
            funct->flags[j++] = str[i++];
        funct->flags[j] = '\0';
    }
    while (str[i] == ' ' && !end_command(str[i]))
        i++;
    int k = 0;
    while (!end_command(str[i]))
    {
        j = 0;
        funct->args[k] = malloc(1024);
        if (!ft_strcmp(funct->type, "echo"))
            while (!end_command(str[i]))
                funct->args[k][j++] = str[i++];
        else
            while (str[i] != ' ' && !end_command(str[i]))
                funct->args[k][j++] = str[i++];
        k++;
        funct->count_args++;
    }
    funct->len = i;
    i++;
    if (str[i])
        return(1);
    return (0);
}