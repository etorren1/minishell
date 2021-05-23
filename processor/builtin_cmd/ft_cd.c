/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 21:17:56 by etorren           #+#    #+#             */
/*   Updated: 2021/05/23 21:17:58 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cd(t_cmd *cmd)
{
	if (cmd->args[0] == 0)
		chdir("/Users");
	else if (chdir(cmd->args[0]) == -1)
		printf("cd: no such file or directory: %s\n", cmd->args[0]);
}
