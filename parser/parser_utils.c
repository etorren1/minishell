/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masharla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 20:38:19 by masharla          #+#    #+#             */
/*   Updated: 2021/05/22 21:52:49 by ruslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

char	*join_and_free(char *prefix, char *body, char *postfix)
{
	char	*result;

	result = ft_strjoin(prefix, body);
	free(body);
	result = ft_strjoin(result, postfix);
	free(postfix);
	return (result);
}

int	find_end(const char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\'')
		{
			i++;
			while (line[i] != '\''
				|| (line[i] == '\'' && is_backslahed(line, i)))
				i++;
		}
		else if (line[i] == '"')
		{
			i++;
			while (line[i] != '"'
				|| (line[i] == '"' && is_backslahed(line, i)))
				i++;
		}
		else if (line[i] == ';' || line[i] == '|')
			break ;
	}
	return (i);
}

int	non_valid_redirect(const char *line)
{
	return (*line == '>' && *(line + 1) && *(line + 1) == '>' && *(line + 2)
		&& (*(line + 2) == '>' || *(line + 2) == '<' || *(line + 2) == '|'));
}

int	ft_strstr_mod(const char *haystack, const char *needle)
{
	int	res;
	int	i;
	int	size;

	if (!needle || needle[0] == '\0')
		return (-2);
	size = ft_strlen(needle);
	res = -1;
	while (haystack[++res])
	{
		if (haystack[res] == needle[0])
		{
			i = 0;
			while (haystack[res + i] && needle[i]
				   && haystack[res + i] == needle[i])
				i++;
			if (size == i)
				return (res);
		}
	}
	return (-1);
}

int	is_line_empty(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (!ft_isspace(line[i]))
			return (0);
	}
	free(line);
	return (1);
}
