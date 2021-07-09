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

static int	is_next_word_number(char *str)
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
	while (line[from - 1] && ft_isspace(line[from - 1]))
		from--;
	return (from);
}

static void	prepare_fd_to(char **line, t_cmd *cmd, int *j,	int *is_valid_amp)
{
	if (cmd->fd_to > 2)
		close(cmd->fd_to);
	if ((*line)[*j] == '&' && is_next_word_number(*line + ++(*j)))
	{
		cmd->fd_to = ft_atoi(*line + *j);
		*is_valid_amp = 1;
		*j += is_next_word_number(*line + *j);
	}
}

static void	define_output_fd(char **line, t_cmd *cmd, int *j, char **env)
{
	int		mode;
	int		from;
	char	*file_name;
	int		is_valid_ampersand;

	is_valid_ampersand = 0;
	from = manual_fd_input(*line, cmd, j);
	mode = count_symbols(*line + *j, '>');
	*j += mode;
	prepare_fd_to(line, cmd, j, &is_valid_ampersand);
	if (!is_valid_ampersand)
	{
		while (ft_isspace((*line)[*j]))
			(*j)++;
		from = *j;
		while ((*line)[*j] && !ft_isspace((*line)[*j]))
		{
			handle_basic_tokens(line, j, env);
			(*j)++;
		}
		file_name = ft_substr(*line, from, *j - from);
		file_operations(file_name, cmd, mode);
		free(file_name);
	}
}

char	*redirect_output(char **line, int *i, t_cmd *cmd, char **env)
{
	int		from;
	int		j;
	char	*prefix;

	j = *i;
	from = manual_fd_input(*line, cmd, i);
	define_output_fd(line, cmd, &j, env);
	prefix = ft_substr(*line, 0, from);
	*i = from - 1;
	return (join_and_free(prefix, ft_strdup(""), ft_strdup(*line + j)));
}
