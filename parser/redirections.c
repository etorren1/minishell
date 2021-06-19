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

int is_next_word_number(char *str) {
	int	i;

	i = 0;
	while (*str && ft_isspace(*str))
		str++;
	while(str[i])
	{
		if (ft_isspace(str[i]))
			break;
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (i);
}

char *redirect(char *line, int *i)
{
	int fd_from;
	int fd_to;
	int from;
	char *prefix;
	char *postfix;

	from = *i;
	fd_to = 0;
	fd_from = 1;
	if (fd_to)
		fd_from = fd_to;
	fd_to = 0;
	while (line[--from])
		if (!ft_isdigit(line[from]))
		{
			if (ft_isspace(line[from]) && from != *i - 1)
				fd_from = ft_atoi(&line[from++]);
			else
				from = *i;
			break ;
		}
	(*i)++;
	prefix = ft_substr(line, 0, from);
	if (line[*i] == '&')
	{
		from = ++(*i);
		if (is_next_word_number(&line[from]))
		{
			fd_to = ft_atoi(&line[from]);
			*i += is_next_word_number(&line[from]);
		}
	}
	if (!fd_to) {
		while (ft_isspace(line[*i]))
			(*i)++;
		from = *i;
		while (line[*i] && !ft_isspace(line[*i]))
			(*i)++;
		postfix = ft_substr(line, from, *i - from);
		fd_to = open(postfix, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		free(postfix);
	}
	postfix = ft_strdup(&line[*i]);
	printf("fd from = %d\n", fd_from);
	printf("fd to = %d\n", fd_to);
	return (join_and_free(prefix, ft_strdup(""), postfix));
}
