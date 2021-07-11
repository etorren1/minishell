/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masharla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 23:10:40 by masharla          #+#    #+#             */
/*   Updated: 2021/06/01 23:10:43 by masharla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

static int	is_pair(const char *str, char c, int *i, int mode)
{
	int	res;

	res = 0;
	while (!res && str[++(*i)])
		if (str[*i] == c && (!mode || !is_backslahed(str, *i)))
			res = 1;
	return (res);
}

static int	is_empty(const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isspace(str[i]))
			break ;
	if (i == ft_strlen(str))
		return (1);
	return (0);
}

static int	is_token(char c)
{
	return (c == '>' || c == '<' || c == '|' || c == '&' || c == ';');
}

static int	is_right_num_of_tokens(const char *c_line, int i)
{
	if (c_line[i] == '>')
	{
		if (c_line[i - 1] && is_token(c_line[i - 1]))
			return (2);
		if (c_line[i + 1] && c_line[i + 1] == '>'
			&& c_line[i + 2] && is_token(c_line[i + 2]))
			return (0);
	}
	else if (c_line[i] == '<')
	{
		if (c_line[i - 1] && is_token(c_line[i - 1]))
			return (2);
		if (c_line[i + 1] && c_line[i + 1] == '<'
			&& c_line[i + 2] && is_token(c_line[i + 2]))
			return (0);
	}
	else if (is_token(c_line[i])
		&& c_line[i + 1] && is_token(c_line[i + 1]))
		return (0);
	return (1);
}

// returns 0 if nothing to parse, -1 if multiline
int	preparser(const char *c_line)
{
	int	i;
	int	res;

	i = -1;
	if (!c_line || is_empty(c_line))
		return (0);
	while (c_line[++i])
	{
		if ((c_line[i] == '\'' && !is_backslahed(c_line, i)
				&& !is_pair(c_line, '\'', &i, 0)) || (c_line[i] == '"'
				&& !is_backslahed(c_line, i) && !is_pair(c_line, '"', &i, 1)))
			return (-1);
		res = is_right_num_of_tokens(c_line, i);
		if (!res)
			return (-1);
		if (res == 2)
			continue ;
	}
	return (1);
}
