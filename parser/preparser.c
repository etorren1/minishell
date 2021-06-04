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

int is_pair(const char *str, char c, int *i)
{
	int	res;

	res = 0;
	while (!res && str[++(*i)])
		if (str[*i] == c)
			res = 1;
	return res;
}

int less_of_limit(const char *str, char c, int *i, int limit)
{
	int	res;

	res = 0;
	while (res < limit && str[++(*i)])
	{
		if (str[*i] != c || !ft_isspace(str[*i]))
			break ;
		if (str[*i] == c)
			res++;
	}
	if (res < limit)
		return (1);
	return (0);
}

int	is_empty(const char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (!ft_isspace(str[i]))
			break ;
	if (i == ft_strlen(str))
		return (1);
	return (0);
}

// returns 0 if nothing to parse, -1 if multiline
int preparser(const char *command_line)
{
	int i;

	i = -1;
	if (!command_line || is_empty(command_line))
		return (0);
	while (command_line[++i])
	{
		if (command_line[i] == '\'' && !is_pair(command_line, '\'', &i))
			return (-1);
		if (command_line[i] == '"' && !is_pair(command_line, '"', &i))
			return (-1);
	}
	return (1);
}
