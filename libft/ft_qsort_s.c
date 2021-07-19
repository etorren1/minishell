/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 15:42:52 by etorren           #+#    #+#             */
/*   Updated: 2021/05/22 15:44:51 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	s_core(char **arr, int beg, int end)
{
	int		left;
	int		right;
	char	*temp;

	left = beg;
	right = end;
	temp = arr[(left + right) / 2];
	if (beg < end)
	{
		while (left <= right)
		{
			while (ft_strcmp(arr[left], temp) < 0)
				left++;
			while (ft_strcmp(arr[right], temp) > 0)
				right--;
			if (left <= right)
			{
				temp = arr[left];
				arr[left++] = arr[right];
				arr[right--] = temp;
			}
		}
		s_core(arr, beg, right);
		s_core(arr, left, end);
	}
}

void	ft_qsort_s(char **arr, int beg, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		if (ft_strcmp(arr[i], arr[i + 1]) > 0)
		{
			s_core(arr, beg, end);
			i = 0;
		}
		i++;
	}
}
