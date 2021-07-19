/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masharla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 18:22:49 by masharla          #+#    #+#             */
/*   Updated: 2021/07/11 18:22:50 by masharla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

static int	handle_heredoc_tokens(char **line, int *i, t_rl *rl)
{
	if ((*line)[*i] == '\\')
		*line = backslash(*line, i);
	else if ((*line)[*i] == '$')
		*line = dollar(*line, i, rl);
	return (1);
}

char	*heredoc(char **line, int *i, t_cmd *cmd, t_rl *rl)
{
	int		j;
	int		k;
	char	*tmp;
	char	*prefix;
	char	*postfix;

	j = *i + 2;
	if (!(*line)[j] || (*line)[j] == -1)
		return (*line);
	while ((*line)[j] != -1)
		j++;
	tmp = ft_substr(*line, *i + 2, j - (*i + 2));
	k = -1;
	if (!rl->mode[rl->mode_count++])
		while (tmp[++k])
			handle_heredoc_tokens(&tmp, &k, rl);
	j += 1 + (ft_isspace((*line)[j + 1]));
	cmd->fd_from = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(cmd->fd_from, tmp, ft_strlen(tmp)); close(cmd->fd_from);
	free(tmp);
	cmd->fd_from = open(".heredoc", O_RDONLY, 0644);
	prefix = ft_substr(*line, 0, *i);
	postfix = ft_strdup(&(*line)[j]);
	free(*line);
	return (join_and_free(prefix, ft_strdup(""), postfix));
}
