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

static void	get_home_dir(char **envp)
{
	int		ret;

	ret = find_environment("HOME", envp);
	if (ret > 0)
		chdir(&envp[ret][5]);
}
static char	*get_pwd(char *env)
{
	int 	size;
	char	*pwd;
	char	*tmp;

	size = 128;
	tmp = NULL;
	tmp = getcwd(tmp, size);
	while (errno == 34)
	{
		size += size;
		errno = 0;
		free(tmp);
		tmp = getcwd(tmp, size);
	}
	pwd = ft_strjoin(ft_strdup(env), tmp);
	free(tmp);
	return (pwd);
}

static void	change_envp(char ***envp, char *old, char *new)
{
	int		ret;

	ret = find_environment("OLDPWD", *envp);
	if (ret >= 0)
	{
		(*envp)[ret] = ft_realloc((*envp)[ret], ft_strlen(old) + 1);
		ft_strcpy((*envp)[ret], old);
		free(old);
	}
	else if (ret == -1)
		*envp = ft_arradd_str_mod(*envp, old, ft_arrsize(*envp) - 1);
	ret = find_environment("PWD", *envp);
	(*envp)[ret] = ft_realloc((*envp)[ret], ft_strlen(new) + 1);
	ft_strcpy((*envp)[ret], new);
}

static void	new_pwd(t_cmd *cmd, char ***envp)
{
	char	*oldpwd;
	char	*newpwd;

	oldpwd = get_pwd("OLDPWD=");
	if (chdir(cmd->args[1]) == -1)
	{
		free(oldpwd);
		printf("cd: no such file or directory: %s\n", cmd->args[1]);
	}
	else if (find_environment("PWD", *envp) > -1)
	{
		newpwd = get_pwd("PWD=");
		change_envp(envp, oldpwd, newpwd);
	}
}

void	ft_cd(t_cmd *cmd, char ***envp)
{
	if (cmd->args[1] == 0)
		get_home_dir(*envp);
	else if (cmd->args[2])
		printf("cd: too many arguments\n");
	else
		new_pwd(cmd, envp);
}
