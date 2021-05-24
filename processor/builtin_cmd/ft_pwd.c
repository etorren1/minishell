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

	size = 1024;
	tmp = malloc(size);
	if (!tmp)
		return ;
	getcwd(tmp, size);
	while (tmp == NULL) // maybe use ERRNO???
	{
		size += size;
		ft_realloc(tmp, size);
		getcwd(tmp, size);
	}
	printf("%s\n", tmp);
	free(tmp);
}
