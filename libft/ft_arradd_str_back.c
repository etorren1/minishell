/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arradd_str_back.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 15:10:12 by etorren           #+#    #+#             */
/*   Updated: 2021/05/23 15:11:18 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arradd_str_back(char **arr, char *str)
{
	int		i;
	int		size;
	char	**tmp;

	i = -1;
	size = ft_arrsize(arr);
	tmp = (char **)malloc(sizeof(arr) * (size + 2));
	while (++i < size)
	{
		tmp[i] = malloc(ft_strlen(arr[i]) + 1);
		ft_strcpy(tmp[i], arr[i]);
	}
	tmp[i] = malloc(ft_strlen(str) + 1);
	ft_strcpy(tmp[i], str);
	tmp[++i] = NULL;
	ft_arrfree(arr);
	return (tmp);
}
