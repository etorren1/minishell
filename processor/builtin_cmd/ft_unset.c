/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 21:18:48 by etorren           #+#    #+#             */
/*   Updated: 2021/05/23 21:18:49 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_environment(char *env, char **envp)
{
	char	*str;
	int		i;
	int		len;

	len = 0;
	while (env[len] != '=' && env[len])
        len++;
	i = -1;
	while (envp[++i])
		if (!ft_strncmp(env, envp[i], len) && envp[i][len] == '=')
			return (i);
	return (-1);
}

void	ft_unset(t_cmd *cmd, char *(**envp))
{
    int     res;
    int     i;

    i = 0;
    while (cmd->args[i])
    {
        res = find_environment(cmd->args[i], *envp);
        if (res >= 0)
            *envp = ft_arrdel_str(*envp, res);
        i++;
    }
}
