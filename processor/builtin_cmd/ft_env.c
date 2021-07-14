/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 21:18:12 by etorren           #+#    #+#             */
/*   Updated: 2021/05/23 21:18:14 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_env(t_cmd *cmd, char **envp)
{
	int i;

	i = 0;
	if (cmd->args[1])
	{
		put_error(NULL, cmd->args[0], cmd->args[1], "No such file or directory");
		return (127);
	}
	while (envp[i])
		ft_putendl_fd(envp[i++], cmd->fd_to);
	return (0);
}
