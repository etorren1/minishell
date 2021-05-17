/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 20:23:08 by etorren           #+#    #+#             */
/*   Updated: 2020/11/22 16:44:52 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	k;

	k = 0;
	if (needle[0] == 0)
		return ((char *)haystack);
	while (k < len && haystack[k])
	{
		if (needle[0] == haystack[k] && k + ft_strlen(needle) <= len)
			if (ft_strncmp(&haystack[k], needle, ft_strlen(needle)) == 0)
				return ((char *)&haystack[k]);
		k++;
	}
	return (0);
}
