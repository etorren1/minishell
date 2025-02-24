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

int	clean_return(char *line, char *prefix)
{
	if (line)
		free(line);
	if (prefix)
		free(prefix);
	return (1);
}

char	*redirect_input(char **line, int *i, t_cmd *cmd, t_rl *rl)
{
	int		from;
	int		j;
	char	*prefix;

	j = *i + 1;
	while ((*line)[j] && ft_isspace((*line)[j]))
		j++;
	from = j;
	while ((*line)[j] && !ft_isspace((*line)[j]))
	{
		handle_basic_tokens(line, &j, rl);
		j++;
	}
	if (*i == j - 1 && clean_return(*line, NULL))
		return (NULL);
	prefix = ft_substr(*line, from, j - from);
	if (cmd->fd_from > 2)
		close(cmd->fd_from);
	if (file_operations(prefix, cmd, 0) < 3 && clean_return(*line, prefix))
		return (NULL);
	free(prefix);
	while ((*line)[*i - 1] && ft_isspace((*line)[*i - 1]))
		(*i)--;
	prefix = ft_substr(*line, 0, *i);
	free(*line);
	return (join_and_free(prefix, ft_strdup(""), ft_strdup(*line + j)));
}
