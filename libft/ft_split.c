/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:00:20 by etorren           #+#    #+#             */
/*   Updated: 2020/11/18 18:01:58 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_rowcount(char const *s, char c)
{
	size_t		i;
	int			check;
	int			rows;

	i = 0;
	rows = 0;
	check = 0;
	while (s[i])
	{
		if (check == 0 && s[i] != c)
		{
			rows++;
			check = 1;
		}
		else if (check == 1 && s[i] == c)
			check = 0;
		i++;
	}
	return (rows);
}

static int	clear_exit(char **arr, int k)
{
	while (k)
		free(arr[k--]);
	return (-1);
}

static int	split_core(char	const *s, char c, char **arr, char *temp)
{
	size_t		i;
	size_t		n;
	int			k;

	i = 0;
	k = 0;
	while (k < ft_rowcount(s, c))
	{
		n = 0;
		if (s[i] != c)
		{
			while (s[i] != c && s[i])
				temp[n++] = s[i++];
			temp[n] = '\0';
			arr[k] = malloc(ft_strlen(temp) + 1);
			if (!arr[k])
				clear_exit(arr, k);
			ft_strcpy(arr[k++], temp);
		}
		i++;
	}
	return (k);
}

char	**ft_split(char const *s, char c)
{
	int			k;
	char		**arr;
	char		*temp;

	if (!s)
		return (0);
	arr = (char **)malloc((ft_rowcount(s, c) + 1) * sizeof(size_t));
	if (!arr)
		return (0);
	temp = (char *)malloc(ft_strlen(s));
	if (!temp)
		return (0);
	k = split_core(s, c, arr, temp);
	if (k == -1)
		free(arr);
	else
		arr[k] = NULL;
	free(temp);
	return (arr);
}
