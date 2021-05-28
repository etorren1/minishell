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
	if (!ft_strcmp(cmd->args[0], "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd->args[0], "cd"))
		ft_cd(cmd, *envp);
	else if (!ft_strcmp(cmd->args[0], "env"))
		ft_env(*envp);
	else if (!ft_strcmp(cmd->args[0], "export"))
		ft_export(cmd, envp);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		ft_unset(cmd, envp);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		ft_exit();
	/*int i = 0;
	while (cmd->args[i]) {
		printf("debug3>>i=%d %s\n", i, cmd->args[i]);
		i++;
	}*/
	/*else
	{
		pid_t pid = fork();
		char *str;
		str = ft_strdup("/bin/");
		str = ft_strjoin(str, cmd->args[0]);
		if (cmd->flags)
			cmd->args = ft_arradd_str(cmd->args, cmd->flags, 1);
		if (pid == 0)
		{
			if (execve(str, cmd->args, *envp) == -1)
				printf("minishell: %s: command not found\n\e[31merrno:\e[0m %s\n\e[31merr_id:\e[0m %d\n", cmd->args[0], strerror(errno), errno);
		}
		else if (pid == -1)
			printf("Error\n");
		else
			wait(NULL);
	}*/
}
