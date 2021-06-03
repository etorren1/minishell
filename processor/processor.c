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
	else
	{
		pid_t pid = fork();
		if (cmd->flags)
			cmd->args = ft_arradd_str(cmd->args, cmd->flags, 1);
		if (pid == 0)
		{
			char **temp;

			temp = malloc(sizeof(temp) * 2);
			temp[0] = malloc(ft_strlen(cmd->args[0]) + 1);
			temp[1] = NULL;
			ft_strcpy(temp[0], cmd->args[0]);
			int ret;
			char *str;

			ret = find_environment("PATH", *envp);
			if (ret != -1)
			{
				//printf("%s\n", (*envp)[ret]);
				int		i = -1;
				int		prev = 0;
				char	*sub;
				str = ft_substr((*envp)[ret], 5, ft_strlen((*envp)[ret]) - 5);
				while (str[++i])
				{
					if (str[i] == ':')
					{
						str[i++] = '/';
						sub = ft_substr(str, prev, i - prev);
						sub = ft_strjoin(sub, cmd->args[0]);
						prev = i;
						temp = ft_arradd_str_mod(temp, sub, ft_arrsize(temp));
					}
				}
				str[i++] = '/';
				sub = ft_substr(str, prev, i - prev);
				sub = ft_strjoin(sub, cmd->args[0]);
				prev = i;
				temp = ft_arradd_str_mod(temp, sub, ft_arrsize(temp));
			}
			int j = 0;
			//while (temp[j])
			//	printf(">>%s\n", temp[j++]);
			j = 0;
			while (execve(temp[j], cmd->args, *envp) == -1 && temp[j])
				j++;
			if (!temp[j])
				printf("minishell: %s: command not found\n\e[31merrno:\e[0m %s\n\e[31merr_id:\e[0m %d\n", cmd->args[0], strerror(errno), errno);
		}
		else if (pid == -1)
			printf("Error\n");
		else
			wait(NULL);
	}
}
