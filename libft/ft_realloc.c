/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 01:00:20 by etorren           #+#    #+#             */
/*   Updated: 2021/05/18 21:54:47 by ruslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *src, size_t size)
{
	char	*new;

	new = (char *)malloc(size + 1);
	ft_bzero(new, size + 1);
	if (!new)
		return (0);
	if (size < ft_strlen(src))
		ft_strlcpy(new, src, size);
	else
		ft_strcpy(new, src);
	free(src);
	return (new);
}
