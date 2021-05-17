/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:19:47 by etorren           #+#    #+#             */
/*   Updated: 2020/11/14 14:36:37 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *arr1, const void *arr2, size_t n)
{
	unsigned char	*temp1;
	unsigned char	*temp2;
	size_t			i;

	temp1 = (unsigned char *)arr1;
	temp2 = (unsigned char *)arr2;
	i = 0;
	while (i < n)
	{
		if (temp1[i] > temp2[i])
			return (temp1[i] - temp2[i]);
		if (temp1[i] < temp2[i])
			return (temp1[i] - temp2[i]);
		i++;
	}
	return (0);
}
