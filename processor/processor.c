/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 21:17:12 by etorren           #+#    #+#             */
/*   Updated: 2021/05/23 21:17:43 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/processor.h"

void	processor(t_cmd *cmd, char *(**envp))
{
	if (!ft_strcmp(cmd->type, "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd->type, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd->type, "cd"))
		ft_cd(cmd);
	else if (!ft_strcmp(cmd->type, "env"))
		ft_env(*envp);
	else if (!ft_strcmp(cmd->type, "export"))
		ft_export(cmd, envp);
	else if (!ft_strcmp(cmd->type, "unset"))
		ft_unset(cmd, envp);
	else if (!ft_strcmp(cmd->type, "exit"))
		ft_exit();
	else
		printf("minishell: %s: command not found\n", cmd->type);
}
