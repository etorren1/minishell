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

void	get_paths(char *path, char *bin, char *(**temp), int ret)
{
	int		i = -1;
	int		prev = 0;
	char	*sub;

	while (path[++i])
	{
		if (path[i] == ':')
		{
			path[i++] = '/';
			sub = ft_substr(path, prev, i - prev);
			sub = ft_strjoin(sub, bin);
			prev = i;
			(*temp) = ft_arradd_str_mod((*temp), sub, ft_arrsize(*temp));
		}
	}
	path[i++] = '/';
	sub = ft_substr(path, prev, i - prev);
	sub = ft_strjoin(sub, bin);
	prev = i;
	(*temp) = ft_arradd_str_mod((*temp), sub, ft_arrsize(*temp));
	free(path);
}

void	subprocess(t_cmd *cmd, char **envp)
{
	char **temp;
	int ret;
	int j;
	char *str;

	dup2(cmd->fd_to, 1);
	dup2(cmd->fd_from, 0);
	temp = malloc(sizeof(temp) * 2);
	temp[0] = malloc(ft_strlen(cmd->args[0]) + 1);
	temp[1] = NULL;
	ft_strcpy(temp[0], cmd->args[0]);	
	ret = find_environment("PATH", envp);
	if (ret != -1)
		get_paths(ft_strdup(envp[ret]), cmd->args[0], &temp, ret);
	j = 0;
	while (execve(temp[j], cmd->args, envp) == -1 && temp[j])
		j++;
	if (!temp[j])
	{
		printf("minishell: %s: command not found\n", cmd->args[0]);
		ft_arrfree(temp);
		exit(-1);
	}
	ft_arrfree(temp);
}

void	binary_cmd(t_cmd *cmd, char **envp)
{
	pid_t pid = fork();
	
	signal(SIGQUIT, print_ouit);
	signal(SIGINT, ctrl_c_handler);
	if (cmd->flags)
		cmd->args = ft_arradd_str(cmd->args, cmd->flags, 1);
	if (pid == 0)
		subprocess(cmd, envp);
	else if (pid == -1)
		printf("PID Error!!!!!!!!!!!!!!!\n");
	else
		wait(NULL);
}

void	processor(t_cmd *cmd, char *(**envp), t_rl *rl)
{
	/*////
	printf("\e[34m>>CMD_INFO<<\n");
	int l = -1;
	while (cmd->args[++l])
		printf("args[%d]=%s\n",l, cmd->args[l]);
	printf("fd_from=%d  fd_to=%d\n", cmd->fd_from, cmd->fd_to);
	printf(">>END<<\e[0m\n");
	*///////
	if (!ft_strcmp(cmd->args[0], "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		ft_pwd(cmd->fd_to);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		ft_cd(cmd, envp);
	else if (!ft_strcmp(cmd->args[0], "env"))
		ft_env(cmd->fd_to, *envp);
	else if (!ft_strcmp(cmd->args[0], "export"))
		ft_export(cmd, envp);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		ft_unset(cmd, envp);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		ft_exit(cmd, rl, *envp);
	else
		binary_cmd(cmd, *envp);
}
