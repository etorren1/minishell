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

int	non_valid_redirect(char *line)
{
	return (*line == '>' && *(line + 1) && *(line + 1) == '>' && *(line + 2)
		&& (*(line + 2) == '>' || *(line + 2) == '<' || *(line + 2) == '|'));
}

void free_cmd(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->args[++i])
		free(cmd->args[i]);
	if (cmd->flags)
		free(cmd->flags);
	free(cmd);
}

void free_arrcmd(t_cmd **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		free_cmd(cmd[i]);
	free(cmd);
}

t_cmd	**ft_arrcmd_addelem(t_cmd **arr, t_cmd *elem)
{
	int	size;
	int	i;
	t_cmd	**new_arr;

	size = 0;
	i = -1;
	while (arr[++i])
		size++;
	new_arr = malloc(sizeof(t_cmd) * size + sizeof(t_cmd) * 2);
	i = -1;
	while (arr[++i])
	{
		new_arr[i] = arr[i];
		arr[i] = NULL;
	}
	new_arr[i++] = elem;
	new_arr[i] = NULL;
	free_arrcmd(arr);
	return new_arr;
}

int	parser(char *command_line, char **env, t_cmd ***cmd)
{
	int	i;
	int j;
	char	*line;
	t_cmd	*tmp;

	i = preparser(command_line);
	if (i <= 0)
		return (i);
	i = 0;
	while (!i || command_line[i - 1] == '|')
	{
		tmp = malloc(sizeof(t_cmd));
		tmp->args = malloc(sizeof (char *));
		*tmp->args = NULL;
		tmp->flags = NULL;
		tmp->fd_from = 1;
		tmp->fd_to = 1;
		tmp->len = find_end(&command_line[i]);
		line = ft_substr(command_line, i, tmp->len);
		j = -1;
		while (line[++j])
			if (!ft_isspace(line[j]))
			{
				if (line[j] == '\'')
					line = single_quotes(line, &j);
				else if (line[j] == '"')
					line = double_quotes(line, env, &j);
				else if (line[j] == '\\')
					line = backslash(line, &j);
				else if (line[j] == '$')
					line = dollar(line, &j, env);
			}
		j = -1;
		while (line[++j])
			if (!ft_isspace(line[j]))
			{
				if (non_valid_redirect(line))
					return (-3);
				else if (line[j] == '>')
					line = redirect_output(line, &j, tmp);
				else if (line[j] == '<')
					line = redirect_input(line, &j, tmp);
				if (!line)
					return (-1);
			}
		if (command_line[i + tmp->len] == '|')
			tmp->len++;
		i += tmp->len;
		retrieve_args(line, tmp);
		retrieve_flags(tmp);
		free(line);
		*cmd = ft_arrcmd_addelem(*cmd, tmp);
	}

//	printf("command line pointer at %c\n", command_line[cmd->len]);
	return (1);
}

/*int	main(int argc, char **argv, char **env)
{
	t_cmd	**cmd = malloc(sizeof(cmd));
	cmd[0] = NULL;

	char *case0 = "  			1";
	char *case1 = "echo co'mma'nd\"000\"\"00\\$00\"'brbrbr'";
	char *case2 = "echo 12345\" я $USER	\"123 ; \";\" ls ;";
	char *case3 = "echo $USER";
	char *case4 = "ls -l -a arg1 arg2 ' ' \" ' \" arg3";
	char *case5 = "echo \"$USER\"";
	char *case6 = "echo -n $USER $USER";
	char *case7 = "echo test > 1";
	char *case8 = "echo test >&0";
	char *case9 = "cat 1 < 2 >&1";
	char *case10 = "echo test > 1 > 2 > 3";
	char *case11 = "cat > 2\\>2";
	char *case12 = "cat > $USER";
	char *case13 = "echo > $USER";
	char *case14 = "cat < 1";
	char *case15 = "> 1 > 2";
	char *case16 = "> 1 > 2 | cat -e";
	char *case17 = "ls | cat -e | grep 1 ; cd parser";


	printf("%d\n", parser(case17, env, &cmd));

	int i = -1;
	while (cmd[++i])
	{
		printf("Element %d\n", i);
		int j = -1;
		while (cmd[i]->args[++j])
			printf("arg[%d] = %s\n", j, cmd[i]->args[j]);
		if (cmd[i]->flags)
			printf("flags = %s\n", cmd[i]->flags);
		printf("fd_from = %d\n", cmd[i]->fd_from);
		printf("fd_to = %d\n", cmd[i]->fd_to);
	}
}*/

// Если cat и !arg[1] то печатаем из fd_from. Если cat и arg[1] то печатаем с
// arg[1]

