/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arradd_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 15:10:12 by etorren           #+#    #+#             */
/*   Updated: 2021/05/23 15:11:18 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arradd_str(char **arr, char *str, int pos)
{
	int		i;
	int		size;
	char	**tmp;

	i = -1;
	size = ft_arrsize(arr);
	if (pos > size || pos < 0)
		return (NULL);
	tmp = (char **)malloc(sizeof(arr) * (size + 2));
	while (++i < pos)
	{
		tmp[i] = malloc(ft_strlen(arr[i]) + 1);
		ft_strcpy(tmp[i], arr[i]);
	}
	tmp[i] = malloc(ft_strlen(str) + 1);
	ft_strcpy(tmp[i], str);
	while (++i < size + 1)
	{
		tmp[i] = malloc(ft_strlen(arr[i - 1]) + 1);
		ft_strcpy(tmp[i], arr[i - 1]);
	}
	tmp[i] = NULL;
	ft_arrfree(arr);
	return (tmp);
}
