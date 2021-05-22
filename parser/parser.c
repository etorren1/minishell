/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masharla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 22:47:59 by masharla          #+#    #+#             */
/*   Updated: 2021/05/22 16:19:21 by ruslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

// Parse incoming string.
int	parser(char **line, t_cmd *cmd)
{
	int	i;

	i = -1;
	while ((*line)[++i])
	{
		if ((*line)[i] == '\'')
			*line = single_quotes(*line, &i);
		else if ((*line)[i] == '"')
			*line = double_quotes(*line, &i);
		else if ((*line)[i] == '\\')
			*line = backslash(*line, &i);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_cmd	cmd;
	char *case1 = strdup("co'mma'nd\"000\"\"0000\"'brbrbr'");

	printf("%s\n", case1);
	parser(&case1, &cmd);
	printf("%s\n", case1);
}
