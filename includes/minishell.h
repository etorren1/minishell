/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 12:51:28 by etorren           #+#    #+#             */
/*   Updated: 2021/05/23 21:16:51 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>

typedef struct  s_cmd {
	char        *flags;
	char        **args;
	int			fd_from;
	int 		fd_to;
	int			len;
}               t_cmd;

int				parser(char *command_line, char **env, t_cmd ***cmd);
void			processor(t_cmd *cmd, char *(**envp));
int				find_environment(char *env, char **envp);
char			*get_absolute_path_process(char *proc);
char			*get_pwd(void);
void			up_shlvl(char ***envp);
char 			**get_dir_content(char *str);
void 			free_arrcmd(t_cmd **cmd);

#endif
