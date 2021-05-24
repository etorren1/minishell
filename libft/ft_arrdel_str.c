/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdel_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 18:48:33 by etorren           #+#    #+#             */
/*   Updated: 2021/05/23 18:49:12 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arrdel_str(char **arr, int pos)
{
	int		i;
	int		size;
	char	**tmp;

	i = -1;
	size = ft_arrsize(arr);
	if (pos > size || pos < 0)
		return (NULL);
	tmp = (char **)malloc(sizeof(char **) * (size));
	while (++i < pos)
	{
		tmp[i] = malloc(ft_strlen(arr[i]) + 1);
		ft_strcpy(tmp[i], arr[i]);
	}
	while (i < size - 1)
	{
		tmp[i] = malloc(ft_strlen(arr[i + 1]) + 1);
		ft_strcpy(tmp[i], arr[i + 1]);
		i++;
	}
	tmp[i] = NULL;
	ft_arrfree(arr);
	return (tmp);
}
