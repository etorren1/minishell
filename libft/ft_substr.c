/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:27:40 by etorren           #+#    #+#             */
/*   Updated: 2020/11/22 16:48:13 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	if (ft_strlen(s) <= start)
		str[0] = '\0';
	while (i < len && s[start] && ft_strlen(s) > start)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
