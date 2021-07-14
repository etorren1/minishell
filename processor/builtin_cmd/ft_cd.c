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

static char *make_pwdenv(char *var, char *val)
{
	char	*env;

	env = ft_strjoin(ft_strdup(var), "=");
	env = ft_strjoin(env, val);
	free(val);
	return(env);
}

static int	new_pwd(t_cmd *cmd, char ***envp)
{
	char	*oldpwd;
	char	*newpwd;

	oldpwd = make_pwdenv("OLDPWD", get_pwd());
	if (chdir(cmd->args[1]) == -1)
	{
		free(oldpwd);
		put_error(NULL, cmd->args[0], cmd->args[1], "No such file or directory");
		return (1);
	}
	else if (find_environment("PWD", *envp) > -1)
	{
		newpwd = make_pwdenv("PWD", get_pwd());
		change_envp(envp, oldpwd, newpwd);
		return (0);
	}
	return (0);
}

int		ft_cd(t_cmd *cmd, char ***envp)
{
	if (cmd->args[1] == 0)
		get_home_dir(*envp);
	else if (cmd->args[2])
	{
		put_error(NULL, cmd->args[0], NULL, "too many arguments");
		return (1);
	}
	else
		return (new_pwd(cmd, envp));
	return (0);
}
