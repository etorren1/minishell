/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 21:17:56 by etorren           #+#    #+#             */
/*   Updated: 2021/05/23 21:17:58 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_home_dir(char **envp)
{
	int		ret;

	ret = find_environment("HOME", envp);
	if (ret > 0)
		chdir(&envp[ret][5]);
}

void	ft_cd(t_cmd *cmd, char **envp)
{
	if (cmd->args[0] == 0)
		get_home_dir(envp);
	else if (chdir(cmd->args[0]) == -1)
		printf("cd: no such file or directory: %s\n", cmd->args[0]);
}
