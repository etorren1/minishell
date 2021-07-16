/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 11:01:12 by etorren           #+#    #+#             */
/*   Updated: 2021/07/16 14:48:45 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**hhcore(char **tmp, char *head, int len)
{
	char	**buf;
	int		j;
	int		i;

	j = -1;
	i = 0;
	buf = malloc(sizeof(char *) * ft_arrsize(tmp));
	buf[0] = NULL;
	while (tmp[++j])
	{
		if (!ft_strncmp(tmp[j], head, len))
		{
			buf[i++] = ft_strdup(tmp[j]);
			buf[i] = NULL;
		}
		free(tmp[j]);
	}
	return (buf);
}

char	**headhandler(char **tmp, int pos, char *str)
{
	int		len;
	char	*head;
	char	**buf;

	len = 0;
	while (pos - 1 - len >= 0 && !ft_isspace(str[pos - 1 - len]))
		len++;
	head = ft_substr(str, pos - len, len);
	buf = hhcore(tmp, head, len);
	free(head);
	free(tmp);
	return (buf);
}

void	tailhandler(char **tmp, char *str, int *pos, t_cmd *cmd)
{
	int		len;
	int		j;
	char	*tail;

	len = 0;
	j = -1;
	while (str[len] && !ft_isspace(str[len]))
		len++;
	tail = ft_substr(str, 0, len);
	while (tmp[++j])
	{
		if (tail[ft_strlen(tail) - 1] != '/')
			if (tmp[j][ft_strlen(tmp[j]) - 1] == '/')
				tmp[j][ft_strlen(tmp[j]) - 1] = 0;
		if (!ft_strecmp(tmp[j], tail))
			cmd->args = ft_arradd_str_back(cmd->args, tmp[j]);
		free(tmp[j]);
	}
	*pos += len + 1;
	free(tmp);
	free(tail);
}

void    wildcard(char *str, int *pos, t_cmd *cmd)
{
	char    **tmp;
	int     j;

	j = -1;
	tmp = get_dir_content(get_pwd());
	if (((!str[*pos + 1] || str[*pos + 1] == '*' || ft_isspace(str[*pos + 1]))
		&& (*pos - 1 >= 0 && (ft_isspace(str[*pos - 1])
		|| str[*pos - 1]=='*'))))
	{
		while (tmp[++j])
			cmd->args = ft_arradd_str_back(cmd->args, tmp[j]);
		ft_arrfree(tmp);
		if (!str[*pos + 1])
			(*pos)++;
	}
	else
	{
		if (*pos - 1 >= 0 && !ft_isspace(str[*pos - 1]))
			tailhandler(headhandler(tmp, *pos, str), &str[*pos + 1], pos, cmd);
		else
			tailhandler(tmp, &str[*pos + 1], pos, cmd);
	}
	while (str[*pos + 1] && ft_isspace(str[*pos + 1]))
		(*pos)++;
	if (str[*pos] && !str[*pos + 1] && ft_isspace(str[*pos]))
		(*pos)++;
}
