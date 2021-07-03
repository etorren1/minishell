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
char	*double_quotes(char *str, char** env, int *i);
char	*ft_strstr(const char *haystack, const char *needle);
int		ft_strstr_mod(const char *haystack, const char *needle);
char	*dollar(char *str, int *i, char **env);
int		preparser(const char *command_line);
char	*redirect_output(char *line, int *i, t_cmd *cmd);
char	*redirect_input(char *line, int *i, t_cmd *cmd);
void	free_arrcmd(t_cmd **cmd);
