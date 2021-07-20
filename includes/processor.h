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

int		ft_echo(t_cmd *cmd);
int		ft_pwd(int fd);
void	ft_exit(t_cmd *cmd, t_rl *rl);
int		ft_cd(t_cmd *cmd, char ***envp);
int		ft_env(t_cmd *cmd, char **envp);
int		ft_unset(t_cmd *cmd, char *(**envp));
int		ft_export(t_cmd *cmd, char *(**envp));

#endif
