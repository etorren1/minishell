/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 21:18:02 by etorren           #+#    #+#             */
/*   Updated: 2021/05/23 21:18:04 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	 ft_echo(t_cmd *cmd)
{
	int	i;
	int	size;

	i = 1;
	size = ft_arrsize(cmd->args);
	if (cmd->flags && ft_strchr(cmd->flags, 'n'))
		while (i < size)
		{
			ft_putstr_fd(cmd->args[i++], cmd->fd_to);
			if (i != size)
				write(cmd->fd_to, " ", 1);
		}
	else if (!cmd->args[1])
		write(cmd->fd_to, "\n", 1);
	else
	{
		while (i < size)
		{
			ft_putstr_fd(cmd->args[i++], cmd->fd_to);
			if (i != size)
				write(cmd->fd_to, " ", 1);
		}
		write(cmd->fd_to, "\n", 1);
	}
	return (0);
}
