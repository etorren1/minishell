/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masharla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 16:19:07 by masharla          #+#    #+#             */
/*   Updated: 2021/05/22 22:11:50 by ruslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

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

// $? $$ $'' $2abc $'2'abc
char	*dollar(char *str, int *i, char **env)
{
	int		start;
	int		e;
	char	*prefix;
	char	*body;
	char	*postfix;

	start = *i;
//	if (!ft_isalpha(str[*i + 1]) && str[*i] != '_')
	while (str[++(*i)])
		if (!ft_isalnum(str[*i]) && str[*i] != '_')
			break ;
	if (*i == start + 1)
		return (str);
	prefix = ft_strjoin(ft_substr(str, start + 1, *i - start - 1), "=");
	e = -1;
	while (env[++e])
		if (ft_strstr_mod(env[e], prefix) == 0)
			break ;
	body = ft_substr(env[e], ft_strlen(prefix),
			ft_strlen(env[e]) - ft_strlen(prefix));
	free(prefix);
	prefix = ft_substr(str, 0, start);
	postfix = ft_strdup(&str[*i + 1]);
	free(str);
	return (join_and_free(prefix, body, postfix));
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
				|| str[*i + 1] == '"') || str[*i + 1] == '\\')
			str = backslash(str, i);
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
