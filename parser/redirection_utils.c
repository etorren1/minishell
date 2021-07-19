/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masharla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 11:04:38 by masharla          #+#    #+#             */
/*   Updated: 2021/07/05 11:04:44 by masharla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	count_symbols(char *line, char c)
{
	int	count;

	count = 0;
	if (c == '>')
	{
		while (*line == c) {
			line++; count++; }
	}
	return (count);
}

int	file_operations(char *file_name, t_cmd *cmd, int mode)
{
	if (mode > 1)
	{
		cmd->fd_to = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		return (cmd->fd_to);
	}
	else if (mode == 1)
	{
		cmd->fd_to = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		return (cmd->fd_to);
	}
	else
	{
		cmd->fd_from = open(file_name, O_RDONLY, 0644);
		if (cmd->fd_from < 3)
			put_error("minishell: ", file_name, NULL,
				"No such file or directory");
		return (cmd->fd_from);
	}
}
