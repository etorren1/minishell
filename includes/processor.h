/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 21:16:00 by etorren           #+#    #+#             */
/*   Updated: 2021/05/23 21:16:04 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESSOR_H
# define PROCESSOR_H

# include "minishell.h"
# include <sys/types.h>
# include <sys/wait.h>

void	ft_echo(t_cmd *cmd);
void	ft_pwd(int fd);
void	ft_exit(t_cmd *cmd, t_rl *rl, char **envp);
void	ft_cd(t_cmd *cmd,char ***envp);
void	ft_env(int fd, char **envp);
void	ft_unset(t_cmd *cmd, char *(**envp));
void	ft_export(t_cmd *cmd, char *(**envp));

#endif
