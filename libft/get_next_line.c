/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:47:32 by etorren           #+#    #+#             */
/*   Updated: 2020/12/13 21:30:26 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>

size_t	cut_str(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
	{
		str[i] = '\0';
		return (i + 1);
	}
	return (i);
}

int	liner(char **str, char *buff, int fd)
{
	int	rd;

	rd = 1;
	while (check_n(*str) == 0 && rd > 0)
	{
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd == -1)
		{
			free(buff);
			free(*str);
			return (-1);
		}
		buff[rd] = '\0';
		*str = ft_strjoin(*str, buff);
	}
	free(buff);
	return (rd);
}

int	get_next_line(int fd, char **line)
{
	char		*buff;
	static char	*str;
	int			rd;
	size_t		i;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (-1);
	rd = liner(&str, buff, fd);
	if (rd == -1)
		return (-1);
	i = cut_str(str);
	*line = ft_strdup(str);
	str = ft_tailsv(str, &str[i]);
	if (rd > 0)
		return (1);
	return (0);
}
