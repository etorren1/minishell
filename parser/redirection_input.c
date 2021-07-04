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

char	*redirect_input(char *line, int *i, t_cmd *cmd)
{
	int		from;
	int		j;
	char	*prefix;

	j = *i + 1;
	while (line[j] && ft_isspace(line[j]))
		j++;
	from = j;
	while (line[j] && !ft_isspace(line[j]))
		j++;
	if (*i == j)
		return (NULL);
	prefix = ft_substr(line, from, j - from);
	if (cmd->fd_from > 2)
		close(cmd->fd_from);
	cmd->fd_from = open(prefix, O_RDONLY, 0644);
	free(prefix);
	if (cmd->fd_from < 3)
		return (NULL);
	prefix = ft_substr(line, 0, *i);
	return (join_and_free(prefix, ft_strdup(""), ft_strdup(&line[j])));
}
