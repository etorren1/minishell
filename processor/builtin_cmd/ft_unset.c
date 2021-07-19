/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 21:18:48 by etorren           #+#    #+#             */
/*   Updated: 2021/05/23 21:18:49 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset(t_cmd *cmd, char *(**envp))
{
	int	res;
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		res = find_environment(cmd->args[i], *envp);
		if (res >= 0)
			*envp = ft_arrdel_str(*envp, res);
		i++;
	}
	return (0);
}
