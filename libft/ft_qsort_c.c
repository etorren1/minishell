/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 15:42:52 by etorren           #+#    #+#             */
/*   Updated: 2021/05/22 15:44:51 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_qsort_c(char *arr, int beg, int end)
{
	int		left;
	int		right;
	char	temp;

	left = beg;
	right = end;
	temp = arr[(left + right) / 2];
	if (beg < end)
	{
		while (left <= right)
		{
			while (arr[left] < temp)
				left++;
			while (arr[right] > temp)
				right--;
			if (left <= right)
			{
				temp = arr[left];
				arr[left++] = arr[right];
				arr[right--] = temp;
			}
		}
		ft_qsort_c(arr, beg, right);
		ft_qsort_c(arr, left, end);
	}
}
