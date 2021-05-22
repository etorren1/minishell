/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masharla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 16:19:07 by masharla          #+#    #+#             */
/*   Updated: 2021/05/22 16:24:05 by ruslan           ###   ########.fr       */
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

char	*backslash(char *str, int *i)
{
	char	*prefix;
	char	*postfix;

	prefix = ft_substr(str, 0, *i);
	postfix = ft_strdup(&str[*i + 1]);
	(*i)--;
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

char	*double_quotes(char *str, int *i)
{
	int		start;
	char	*prefix;
	char	*body;
	char	*postfix;

	start = *i;
	while (str[++(*i)])
	{
		if (str[*i] == '\\' && (str[*i + 1] == '\\' || str[*i + 1] == '$'
				|| str[*i + 1] == '"') || str[*i + 1] == '\\')
			str = backslash(str, i);
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
