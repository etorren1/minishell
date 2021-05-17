/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 15:50:07 by etorren           #+#    #+#             */
/*   Updated: 2020/11/14 14:36:54 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*temp2;
	char		*temp1;

	temp1 = dest;
	temp2 = src;
	if (!temp1 && !temp2)
		return (0);
	while (n--)
		temp1[n] = temp2[n];
	return (temp1);
}
