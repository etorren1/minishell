/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masharla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 11:36:34 by masharla          #+#    #+#             */
/*   Updated: 2021/07/04 11:36:35 by masharla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

static char	*take_from_op_status(int status, int *i)
{
	int		len;
	char	*body;

	len = ft_numsize(status);
	body = ft_calloc(len + 1, 1);
	(*i) += len;
	if (status < 0)
	{
		status *= -1;
		body[0] = '-';
	}
	if (!status)
		body[--len] = 48;
	else
	{
		while (status > 0)
		{
			body[--len] = status % 10 + 48;
			status /= 10;
		}
	}
	return (body);
}

static char	*take_from_env(char *str, char **env, int *i, int *e)
{
	int		start;
	char	*body;
	char	*tmp;

	start = *i - 1;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	if (*i == start + 1)
	{
		(*i)--;
		return (ft_strdup(""));
	}
	tmp = ft_strjoin(ft_substr(str, start + 1, *i - start - 1), "=");
	*e = -1;
	while (env[++(*e)])
		if (ft_strstr_mod(env[*e], tmp) == 0)
			break ;
	if (env[*e])
		body = ft_substr(env[*e], ft_strlen(tmp),
				ft_strlen(env[*e]) - ft_strlen(tmp));
	else
		body = ft_strdup("");
	*e = ft_strlen(body) - ft_strlen(tmp) - 1;
	free(tmp);
	return (body);
}

//$'' $2abc $'2'abc
char	*dollar(char *str, int *i, t_rl *rl)
{
	int		start;
	int		e;
	char	*prefix;
	char	*body;
	char	*postfix;

	start = (*i)++;
	if (!str[*i] || (str[*i] && ft_isspace(str[*i])))
		return (str);
	e = 0;
	if (str[*i] && str[*i] == '?')
	{
		body = take_from_op_status(rl->status, i);
		e -= 2;
	}
	else
		body = take_from_env(str, rl->env, i, &e);
	prefix = ft_substr(str, 0, start);
	postfix = ft_strdup(&str[*i]);
	*i += e;
	free(str);
	return (join_and_free(prefix, body, postfix));
}
