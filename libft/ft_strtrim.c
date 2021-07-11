/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 23:08:53 by etorren           #+#    #+#             */
/*   Updated: 2020/11/18 18:01:31 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_chrcmp(char const *set, char const c)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(set))
	{
		if (set[i] - c == 0)
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strtrim(char *s1, char const *set)
{
	size_t		i;
	size_t		start;
	char		*str;

	if (!s1 || !set)
		return (0);
	i = 0;
	while (ft_chrcmp(set, s1[i]) == 0)
		i++;
	start = i;
	i = ft_strlen(s1) - 1;
	while (ft_chrcmp(set, s1[i]) == 0 && i > start)
		i--;
	i++;
	str = ft_substr(s1, start, i - start);
	free(s1);
	return (str);
}
