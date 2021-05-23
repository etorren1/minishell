/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:51:38 by etorren           #+#    #+#             */
/*   Updated: 2020/11/18 18:00:39 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(long num)
{
	int		i;

	i = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		num = -num;
		i++;
	}
	while (num > 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int val)
{
	int		i;
	long	num;
	char	*str;

	i = 0;
	num = val;
	str = (char *)malloc(ft_size(num) + 1);
	if (!str)
		return (0);
	str[0] = '0';
	str[1] = '\0';
	if (val < 0)
		num = -num;
	while (num > 0)
	{
		str[i] = num % 10 + '0';
		num = num / 10;
		i++;
	}
	if (val < 0)
		str[i++] = '-';
	if (i != 0)
		str[i] = '\0';
	return (ft_strrev(str));
}
