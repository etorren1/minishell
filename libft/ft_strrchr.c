/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 21:12:48 by etorren           #+#    #+#             */
/*   Updated: 2020/11/14 14:41:31 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	int	i;
	int	k;

	i = 0;
	k = -1;
	if (str[0] == '\0' && ch == '\0')
		k = i;
	while (str[i])
	{
		if (str[i] == ch)
			k = i;
		i++;
		if (ch == '\0')
			k = i;
	}
	if (k >= 0)
		return ((char *)&str[k]);
	return (NULL);
}
