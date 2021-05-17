/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 20:16:46 by etorren           #+#    #+#             */
/*   Updated: 2020/11/14 14:40:43 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	unsigned char	*temp1;
	unsigned char	*temp2;
	size_t			i;

	temp1 = (unsigned char *)str1;
	temp2 = (unsigned char *)str2;
	i = 0;
	while (i < n && (str1[i] || str2[i]))
	{
		if (temp1[i] > temp2[i])
			return (1);
		else if (temp1[i] < temp2[i])
			return (-1);
		i++;
	}
	if (temp1[0] == '\0' && temp2[0] && n)
		return (-1);
	if (temp1[0] && temp2[0] == '\0' && n)
		return (1);
	return (0);
}
