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

void	retrieve_flags(t_cmd *cmd)
{
	char	*flags;

	if (!cmd->args[0] || cmd->args[0][0] == '-' || !cmd->args[1])
		return ;
	flags = ft_strdup("-");
	while (cmd->args[1] && cmd->args[1][0] == '-')
	{
		flags = ft_strjoin(flags, &cmd->args[1][1]);
		cmd->args = ft_arrdel_str(cmd->args, 1);
	}
	if (ft_strlen(flags) == 1)
	{
		free(flags);
		flags = NULL;
	}
	cmd->flags = flags;
}

void	retrieve_args(const char *str, t_cmd *cmd)
{
	int	start;
	int	end;
	int	arg;

	arg = 0;
	start = 0;
	while (str[start])
	{
		if (!ft_isspace(str[start])) {
			end = start;
			while (str[end] && !ft_isspace(str[end]))
				end++;
			cmd->args = ft_arradd_str_mod(cmd->args, ft_substr(str, start,
					end - start), arg++);
			start = end - 1;
		}
		start++;
	}
	cmd->args[arg] = NULL;
}

int	find_end(const char *line)
{
	int	i;

	i = -1;
	while (line[++i]){
		if (line[i] == '\'')
		{
			i++;
			while (line[i] != '\'')
				i++;
		}
		else if (line[i] == '"')
		{
			i++;
			while (line[i] != '"')
				i++;
		}
		else if(line[i] == ';' || line[i] == '|')
			break ;
	}
	return (i);
}

int	parser(char *command_line, char **env, t_cmd *cmd)
{
	int	i;
	char *line;

	i = preparser(command_line);
	if (i <= 0)
		return (i);
	i = -1;
	cmd->len = find_end(command_line);
	line = ft_substr(command_line, 0, cmd->len);
	while (line[++i])
		if (!ft_isspace(line[i]))
		{
			if (line[i] == '\'')
				line = single_quotes(line, &i);
			else if (line[i] == '"')
				line = double_quotes(line, env, &i);
			else if (line[i] == '\\')
				line = backslash(line, &i);
			else if (line[i] == '$')
				line = dollar(line, &i, env);
			else if (line[i] == '|')
				;
			else if (line[i] == '>')
				line = redirect(line, &i);
			else if (line[i] == '>' && line[i + 2] == '>')
				return (-3);
			else if (line[i] == '>' && line[i + 1] == '>')
				;
			else if (line[i] == '<')
				;
		}
	retrieve_args(line, cmd);
	retrieve_flags(cmd);
	free(line);
	return (1);
}

/*int	main(int argc, char **argv, char **env)
{
	t_cmd	*cmd = malloc(sizeof(t_cmd));
	cmd->args = malloc(sizeof (char *));
	*cmd->args = NULL;
	char *case0 = "  			1";
	char *case1 = "echo co'mma'nd\"000\"\"00\\$00\"'brbrbr'";
	char *case2 = "echo 12345\" я $USER	\"123 ; \";\" ls ;";
	char *case3 = "echo $USER";
	char *case4 = "ls -l -a arg1 arg2 ' ' \" ' \" arg3";
	char *case5 = "echo \"$USER\"";
	char *case6 = "echo -n $USER $USER";
	char *case7 = "echo test > 1";
	char *case8 = "echo test >&1";
	char *case9 = "echo test 2>&2";
	char *case10 = "echo test 3>&2asd";

	printf("%d\n", parser(case10, env, cmd));

	int i = -1;
	while (cmd->args[++i])
		printf("arg[%d] = %s\n", i , cmd->args[i]);
	if (cmd->flags)
		printf("flags = %s\n", cmd->flags);
}*/

