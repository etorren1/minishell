/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masharla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 18:32:33 by masharla          #+#    #+#             */
/*   Updated: 2021/06/07 18:32:40 by masharla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	is_next_word_number(char *str)
{
	int	i;

	i = 0;
	while (*str && ft_isspace(*str))
		str++;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			break ;
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (i);
}

int	count_symbols(char *line, char c)
{
	int	count;

	count = 0;
	while (*line == c)
		line++ && count++;
	return (count);
}

static int	manual_fd_input(char *line, t_cmd *cmd, int *i)
{
	int	j;
	int	from;

	j = *i;
	from = j;
	while (from && line[--from])
	{
		if (!ft_isdigit(line[from]))
		{
			if (ft_isspace(line[from]) && from != j - 1)
			{
				if (cmd->fd_from > 2)
					close(cmd->fd_from);
				cmd->fd_from = ft_atoi(&line[from++]);
				*i = from;
			}
			else
				from = j;
			break ;
		}
	}
	return (from);
}

static void	define_output_fd(char *line, t_cmd *cmd, int *j, int from)
{
	int		mode;
	char	*file_name;
	int		is_valid_ampersand;

	is_valid_ampersand = 0;
	mode = count_symbols(&line[*j], '>');
	*j += mode;
	if (cmd->fd_to > 2)
		close(cmd->fd_to);
	if (line[*j] == '&' && is_next_word_number(&line[++(*j)]))
	{
		cmd->fd_to = ft_atoi(&line[*j]);
		is_valid_ampersand = 1;
		*j += is_next_word_number(&line[*j]);
	}
	if (!is_valid_ampersand)
	{
		while (ft_isspace(line[*j]))
			(*j)++;
		from = *j;
		while (line[*j] && !ft_isspace(line[*j]))
			(*j)++;
		file_name = ft_substr(line, from, *j - from);
		if (mode > 1)
			cmd->fd_to = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			cmd->fd_to = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		free(file_name);
	}
}

char	*redirect_output(char *line, int *i, t_cmd *cmd)
{
	int		from;
	int		j;
	char	*prefix;

	j = *i;
	from = manual_fd_input(line, cmd, i);
	define_output_fd(line, cmd, &j, from);
	prefix = ft_substr(line, 0, from);
	return (join_and_free(prefix, ft_strdup(""), ft_strdup(&line[j])));
}
