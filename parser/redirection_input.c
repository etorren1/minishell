/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masharla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 19:23:52 by masharla          #+#    #+#             */
/*   Updated: 2021/06/23 19:23:55 by masharla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

char	*redirect_input(char **line, int *i, t_cmd *cmd, char **env)
{
	int		from;
	int		j;
	char	*prefix;

	j = *i + 1;
	while ((*line)[j] && ft_isspace((*line)[j]))
		j++;
	from = j;
	while ((*line)[j] && !ft_isspace((*line)[j]))
		handle_basic_tokens(line, &j, env) && j++;
	if (*i == j)
		return (NULL);
	prefix = ft_substr(*line, from, j - from);
	if (cmd->fd_from > 2)
		close(cmd->fd_from);
	if (file_operations(prefix, cmd, 0) < 3)
		return (NULL);
	free(prefix);
	while ((*line)[*i - 1] && ft_isspace((*line)[*i - 1]))
		(*i)--;
	prefix = ft_substr(*line, 0, *i);
	free(*line);
	return (join_and_free(prefix, ft_strdup(""), ft_strdup(*line + j)));
}
