/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 21:18:26 by etorren           #+#    #+#             */
/*   Updated: 2021/05/23 21:18:28 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_environment_mod(char *env, char **envp)
{
	char	*str;
	int		i;
	int		len;

	len = 0;
	while (env[len] != '=')
		if (!env[++len])
			return (-2);
	i = -1;
	while (envp[++i])
		if (!ft_strncmp(env, envp[i], len) && envp[i][len] == '=')
			return (i);
	return (-1);
}

static void	output_envvar(char **envp)
{
	char	**tmp;
	int	 	size;

	size = ft_arrsize(envp);
	tmp = (char **)malloc(sizeof(envp) * (size + 1));
	ft_arrcpy(tmp, envp);
	ft_qsort_s(tmp, 0, ft_arrsize(tmp) - 1);
	size = 0;
	while (tmp[size])
		printf("%s\n", tmp[size++]);
	ft_arrfree(tmp);
}

static void	add_envvar(t_cmd *cmd, char *(**envp))
{
	int		i;
	int		res;

	i = 1;
	while (cmd->args[i])
	{
		printf("debug>>i=%d %s\n", i, cmd->args[i]);
		res = find_environment_mod(cmd->args[i], *envp);
		if (res >= 0)
		{
			ft_realloc((*envp)[res], ft_strlen(cmd->args[i]) + 1);
			ft_strcpy((*envp)[res], cmd->args[i]);
		}
		else if (res == -1)
			*envp = ft_arradd_str(*envp, cmd->args[i], ft_arrsize(*envp) - 1);
		i++;
	}
}

void	ft_export(t_cmd *cmd, char *(**envp))
{

	if (!cmd->args[1])
		output_envvar(*envp);
	else
		add_envvar(cmd, envp);
	/*int i = 0;
	while (cmd->args[i]) {
		printf("debug2>>i=%d %s\n", i, cmd->args[i]);
		i++;
	}*/
}
