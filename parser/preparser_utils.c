/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masharla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 21:49:15 by masharla          #+#    #+#             */
/*   Updated: 2021/07/11 21:49:16 by masharla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	is_backslahed(const char *str, int i)
{
	int	count;

	count = 0;
	while (str[--i] && str[i] == '\\')
		count++;
	if (count && (count % 2))
		return (1);
	return (0);
}
