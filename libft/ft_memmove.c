/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 16:21:40 by etorren           #+#    #+#             */
/*   Updated: 2020/11/14 14:37:09 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*temp2;
	char		*temp1;
	size_t		i;

	temp1 = dest;
	temp2 = src;
	i = 0;
	if (dest == 0 && src == 0)
		return (0);
	else if (dest < src)
	{
		while (i < n)
		{
			temp1[i] = temp2[i];
			i++;
		}
	}
	else
		while (n--)
			temp1[n] = temp2[n];
	return (temp1);
}
