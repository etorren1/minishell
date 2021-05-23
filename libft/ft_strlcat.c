/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 21:38:11 by etorren           #+#    #+#             */
/*   Updated: 2020/11/14 14:39:50 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	destlen;
	size_t	srclen;
	size_t	maxlen;

	i = 0;
	destlen = 0;
	srclen = ft_strlen(src);
	while (dest[destlen] && destlen < dstsize)
		destlen++;
	if (destlen == dstsize)
		return (srclen + destlen);
	maxlen = dstsize - destlen - 1;
	while (i < maxlen && src[i] != '\0')
	{
		dest[destlen + i] = src[i];
		i++;
	}
	dest[destlen + i] = '\0';
	return (destlen + srclen);
}
