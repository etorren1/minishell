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

void	 ft_echo(t_cmd *cmd)
{
	int	i;
	int	size;

	i = 1;
	size = ft_arrsize(cmd->args);
	if (cmd->flags && ft_strchr(cmd->flags, 'n'))
		while (i < size)
		{
			ft_putstr_fd(cmd->args[i++], 1);
			if (i != size)
				write(1, " ", 1);
		}
	else if (!cmd->args[1])
		write(1, "\n", 1);
	else
	{
		while (i < size)
		{
			ft_putstr_fd(cmd->args[i++], 1);
			if (i != size)
				write(1, " ", 1);
		}
		write(1, "\n", 1);
	}
}
