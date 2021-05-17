/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 19:21:53 by etorren           #+#    #+#             */
/*   Updated: 2020/11/14 17:00:15 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	nbr;
	int	np;
	int	i;

	nbr = 0;
	np = 1;
	i = 0;
	while (str[i] != '\0' && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'\
	|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
		i++;
	if (str[i] == '-')
	{
		i++;
		np = -1;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && (str[i] >= 48 && str[i] <= 57))
	{
		nbr = nbr * 10 + (str[i] - 48);
		i++;
	}
	return (np * nbr);
}
