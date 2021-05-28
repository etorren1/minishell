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
	if (ft_strchr(cmd->flags, 'n'))
		write(1, cmd->args[1], ft_strlen(cmd->args[1]));
	else
		printf("%s\n", cmd->args[1]);
}
