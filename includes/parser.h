/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masharla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 16:15:58 by masharla          #+#    #+#             */
/*   Updated: 2021/05/22 22:01:05 by ruslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_and_free(char *prefix, char *body, char *postfix);
char	*backslash(char *str, int *i);
char	*single_quotes(char *str, int *i);
char	*double_quotes(char *str, t_rl *rl, int *i);
int		ft_strstr_mod(const char *haystack, const char *needle);
char	*dollar(char *str, int *i, t_rl *rl);
int		preparser(const char *command_line);
int		handle_basic_tokens(char **line, int *i, t_rl *rl);
char	*redirect_output(char **line, int *i, t_cmd *cmd, t_rl *rl);
char	*redirect_input(char **line, int *i, t_cmd *cmd, t_rl *rl);
t_cmd	*new_cmd();
t_cmd	**ft_arrcmd_addelem(t_cmd **arr, t_cmd *elem);
int		find_end(const char *line);
int		non_valid_redirect(const char *line);
int		count_symbols(char *line, char c);
int		file_operations(char *file_name, t_cmd *cmd, int mode);
int		is_backslahed(const char *str, int i);
int		is_line_empty(char *line, int *res);
char	*heredoc(char **line, int *i, t_cmd *cmd, t_rl *rl);
int		free_cmd(t_cmd *cmd);
void    wildcard(char *str, int *pos, t_cmd *cmd, int *start);

