/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masharla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 22:47:59 by masharla          #+#    #+#             */
/*   Updated: 2021/05/22 22:01:05 by ruslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	parser(const char **command_line, char **env, t_cmd *cmd)
{
	int	i;
	char *line;

	i = -1;
	line = ft_strdup(*command_line);
	while (line[++i])
	{
		cmd->len++;
		if (line[i] == '\'')
			line = single_quotes(line, &i);
		else if (line[i] == '"')
			line = double_quotes(line, env, &i);
		else if (line[i] == '\\')
			line = backslash(line, &i);
		else if (line[i] == '$')
			line = dollar(line, &i, env);
	}
	printf("%s\n", line);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_cmd	cmd;
	const char *case1 = "co'mma'nd\"000\"\"00\\$00\"'brbrbr'";
	const char *case2 = "12345\"$USER\"123";

	printf("%s\n", case1);
	parser(&case2, env, &cmd);

//	char *long_str = "Foo Bar Baz";
//	char *short_str = "Bar";
//	printf("%s\n", strstr(long_str, short_str));
//	printf("%s\n", ft_strstr(long_str, short_str));
//	printf("%d\n", ft_strstr_mod(long_str, short_str));
}
