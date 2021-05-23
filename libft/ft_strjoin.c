/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 22:26:14 by etorren           #+#    #+#             */
/*   Updated: 2020/11/14 14:39:36 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	len;
	size_t	size2;
	size_t	size1;

	if (!s1)
		size1 = 0;
	else
		size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	len = size2 + size1 - 1;
	i = len + 1;
	str = (char *)malloc(size1 + size2 + 1);
	if (!str)
		return (0);
	while (size2--)
		str[len--] = s2[size2];
	while (size1--)
		str[len--] = s1[size1];
	str[i] = '\0';
	free((char *)s1);
	return (str);
}
