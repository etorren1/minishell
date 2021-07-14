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

static void	output_envvar(int fd, char **envp)
{
	char	**tmp;
	int	 	size;

	size = ft_arrsize(envp);
	tmp = (char **)malloc(sizeof(envp) * (size + 1));
	ft_arrcpy(tmp, envp);
	ft_qsort_s(tmp, 0, ft_arrsize(tmp) - 1);
	size = 0;
	while (tmp[size])
		ft_putendl_fd(tmp[size++], fd);
	ft_arrfree(tmp);
}

static int	ft_othersymb(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) || ft_isdigit(str[i]))
			i++;
		else
			return (1);
	}
	return (0);
}

static int	add_envvar(t_cmd *cmd, char *(**envp))
{
	int		i;
	int		res;

	i = 1;
	while (cmd->args[i])
	{
		if (ft_atoi(cmd->args[i]) != 0)
		{
			put_error(NULL, cmd->args[0], cmd->args[i], "not an identifier");
			return (1);
		}
		else if (ft_othersymb(cmd->args[i]))
		{
			put_error(NULL, cmd->args[0], cmd->args[i], "not valid in this context");
			return (1);
		}
		res = find_environment_mod(cmd->args[i], *envp);
		if (res >= 0)
		{
			(*envp)[res] = ft_realloc((*envp)[res], ft_strlen(cmd->args[i]) + 1);
			ft_strcpy((*envp)[res], cmd->args[i]);
		}
		else
		{
			if (res == -2)
				cmd->args[i] = ft_strjoin(cmd->args[i], "=");
			*envp = ft_arradd_str(*envp, cmd->args[i], ft_arrsize(*envp) - 1);
		}
		i++;
	}
	return (0);
}

int	ft_export(t_cmd *cmd, char *(**envp))
{

	if (!cmd->args[1])
	{
		output_envvar(cmd->fd_to, *envp);
		return (0);
	}
	else
		return (add_envvar(cmd, envp));
}
