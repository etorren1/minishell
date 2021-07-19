/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 15:08:06 by etorren           #+#    #+#             */
/*   Updated: 2021/05/23 15:08:28 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arrcpy(char **dest, char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		dest[i] = malloc(ft_strlen(arr[i]) + 1);
		ft_strcpy(dest[i], arr[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
