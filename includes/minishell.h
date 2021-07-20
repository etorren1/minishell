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
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# define BUF_SIZE	12
# define PROMPT		26
# define MINISHELL	"\033[1;32mminishell-0.6$ \033[0m"
# define HISTORY	".minishell_history"

typedef struct s_cmd {
	char		*flags;
	char		**args;
	int			fd_from;
	int			fd_to;
	int			len;
}	t_cmd;

typedef struct s_rl
{
	int		count_symb;
	int		cursor_pos;
	int		len;
	int		fd;
	int		plen;
	int		*mode;
	int		mode_count;
	int		status;
	char	*command_line;
	char	*last_insert;
	char	*buf;
	char	*history;
	char	**env;
	t_node	*histnode;
}	t_rl;

typedef struct s_pip {
	int		**fds;
	int		*pid;
	int		j;
}	t_pip;

int			parser(char *command_line, t_rl *rl, t_cmd ***cmd);
void		processor(t_cmd *cmd, char *(**envp), t_rl *rl);
void		core(t_rl *rl, int k);
void		put_error(char *prefix, char *cmd, char *args, char *err);
int			find_environment(char *env, char **envp);
char		*get_absolute_path_process(char *proc);
char		*get_pwd(void);
void		mem_add(t_rl *rl);
void		up_shlvl(char ***envp);
char		**get_dir_content(char *str);
void		free_arrcmd(t_cmd **cmd);
void		ctrl_c_handler(int sig);
void		print_ouit(int sig);
void		clear_exit(t_rl *rl);

#endif
