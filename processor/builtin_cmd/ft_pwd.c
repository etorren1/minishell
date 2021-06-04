/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 21:18:38 by etorren           #+#    #+#             */
/*   Updated: 2021/05/23 21:18:41 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(void)
{
	int		size;
	char	*tmp;

	size = 5;
	tmp = NULL;
	tmp = getcwd(tmp, size);
	while (errno == 34)
	{
		size += size;
		errno = 0;
		free(tmp);
		tmp = getcwd(tmp, size);
	}
	printf("%s\n", tmp);
	free(tmp);
}
