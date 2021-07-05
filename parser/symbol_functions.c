/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masharla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 16:19:07 by masharla          #+#    #+#             */
/*   Updated: 2021/06/05 22:21:32 by masharla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

char	*backslash(char *str, int *i)
{
	char	*prefix;
	char	*postfix;

	prefix = ft_substr(str, 0, *i);
	postfix = ft_strdup(&str[*i + 1]);
	free(str);
	return (join_and_free(prefix, ft_strdup(""), postfix));
}

char	*single_quotes(char *str, int *i)
{
	int		start;
	char	*prefix;
	char	*body;
	char	*postfix;

	start = *i;
	while (str[++(*i)])
		if (str[*i] == '\'')
			break ;
	prefix = ft_substr(str, 0, start);
	body = ft_substr(str, start + 1, *i - start - 1);
	postfix = ft_strdup(&str[*i + 1]);
	*i -= 2;
	free(str);
	return (join_and_free(prefix, body, postfix));
}

char	*double_quotes(char *str, char **env, int *i)
{
	int		start;
	char	*prefix;
	char	*body;
	char	*postfix;

	start = *i;
	while (str[++(*i)])
	{
		if (str[*i] == '\\' && (str[*i + 1] == '\\' || str[*i + 1] == '$'
				|| str[*i + 1] == '"'))
		{
			str = backslash(str, i);
			(*i)++;
		}
		if (str[*i] == '$')
			str = dollar(str, i, env);
		if (str[*i] == '"')
			break ;
	}
	prefix = ft_substr(str, 0, start);
	body = ft_substr(str, start + 1, *i - start - 1);
	postfix = ft_strdup(&str[*i + 1]);
	*i -= 2;
	free(str);
	return (join_and_free(prefix, body, postfix));
}

void	handle_basic_tokens(char **line, int *i, char **env)
{
	if ((*line)[*i] == '\'')
		*line = single_quotes(*line, i);
	else if ((*line)[*i] == '"')
		*line = double_quotes(*line, env, i);
	else if ((*line)[*i] == '\\')
		*line = backslash(*line, i);
	else if ((*line)[*i] == '$')
		*line = dollar(*line, i, env);
}
