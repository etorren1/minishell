/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masharla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 22:17:22 by masharla          #+#    #+#             */
/*   Updated: 2021/07/03 22:17:24 by masharla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->args = malloc(sizeof (char *));
	*cmd->args = NULL;
	cmd->flags = NULL;
	cmd->fd_from = 1;
	cmd->fd_to = 1;
	return (cmd);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->args[++i])
		free(cmd->args[i]);
	if (cmd->flags)
		free(cmd->flags);
	free(cmd);
}

void	free_arrcmd(t_cmd **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		free_cmd(cmd[i]);
	free(cmd);
}

t_cmd	**ft_arrcmd_addelem(t_cmd **arr, t_cmd *elem)
{
	int		size;
	int		i;
	t_cmd	**new_arr;

	size = 0;
	i = -1;
	while (arr[++i])
		size++;
	new_arr = malloc(sizeof(t_cmd) * size + sizeof(t_cmd) * 2);
	i = -1;
	while (arr[++i])
	{
		new_arr[i] = arr[i];
		arr[i] = NULL;
	}
	new_arr[i++] = elem;
	new_arr[i] = NULL;
	free_arrcmd(arr);
	return (new_arr);
}
