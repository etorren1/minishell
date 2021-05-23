/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:47:19 by etorren           #+#    #+#             */
/*   Updated: 2020/12/13 21:20:07 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

char	*ft_tailsv(char *s1, char *str)
{
	char	*new;
	size_t	i;

	i = -1;
	if (!str)
		return (0);
	if (!str[i + 1])
	{
		free(s1);
		return (0);
	}
	new = (char *)malloc(ft_strlen(str) + 1);
	if (!new)
	{
		free(s1);
		return (0);
	}
	while (str[++i])
		new[i] = str[i];
	new[i] = '\0';
	free(s1);
	return (new);
}

int	check_n(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
