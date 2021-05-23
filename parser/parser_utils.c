/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masharla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 20:38:19 by masharla          #+#    #+#             */
/*   Updated: 2021/05/22 21:52:49 by ruslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

char	*join_and_free(char *prefix, char *body, char *postfix)
{
	char	*result;

	result = ft_strjoin(prefix, body);
	free(body);
	result = ft_strjoin(result, postfix);
	free(postfix);
	return (result);
}

long long	ft_strchr_mod(const char *str, char c)
{
	long	i;

	if (!str)
		return (-2);
	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	char	*ptr;
	size_t	i;
	size_t	size;

	ptr = (char *)haystack;
	if (!needle || needle[0] == '\0')
		return (ptr);
	size = ft_strlen(needle);
	while (*ptr)
	{
		if (*ptr == needle[0])
		{
			i = 0;
			while (ptr[i] && needle[i] && ptr[i] == needle[i])
				i++;
			if (size == i)
				return (ptr);
		}
		ptr++;
	}
	return (0);
}

int	ft_strstr_mod(const char *haystack, const char *needle)
{
	int	res;
	int	i;
	int	size;

	if (!needle || needle[0] == '\0')
		return (-2);
	size = ft_strlen(needle);
	res = -1;
	while (haystack[++res])
	{
		if (haystack[res] == needle[0])
		{
			i = 0;
			while (haystack[res + i] && needle[i]
				   && haystack[res + i] == needle[i])
				i++;
			if (size == i)
				return (res);
		}
	}
	return (-1);
}
