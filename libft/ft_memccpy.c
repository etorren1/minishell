/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 16:01:19 by etorren           #+#    #+#             */
/*   Updated: 2020/11/14 14:44:37 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	const char		*temp2;
	unsigned char	*temp1;
	unsigned char	s;
	size_t			i;

	temp1 = dest;
	temp2 = src;
	s = c;
	i = 0;
	while (i < n)
	{
		temp1[i] = temp2[i];
		if (temp1[i] == s)
			return ((void *)&temp1[++i]);
		i++;
	}
	return (NULL);
}
