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

void	ft_echo(t_cmd *cmd);
void	ft_pwd(void);
void	ft_exit(void);
void	ft_cd(t_cmd *cmd);
void	ft_env(char **envp);
void	ft_unset(t_cmd *cmd, char *(**envp));
void	ft_export(t_cmd *cmd, char *(**envp));

#endif
