/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:25:50 by etorren           #+#    #+#             */
/*   Updated: 2020/11/18 17:35:04 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int		n;
	int		i;
	char	temp;

	i = 0;
	n = ft_strlen(str) - 1;
	while (i < n)
	{
		temp = str[i];
		str[i++] = str[n];
		str[n--] = temp;
	}
	return (str);
}
