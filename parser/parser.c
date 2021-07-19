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

static void	retrieve_flags(t_cmd *cmd)
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

static void	retrieve_next_arg(const char *ln, t_cmd *cmd, int *start, int *i)
{
	char	*arg;
	int		arg_num;

	if (!(ln)[*i] || ((ln)[(*i)++] && (!(ln)[*i] || ft_isspace((ln)[*i]))))
	{
		arg = ft_substr(ln, *start, *i - *start);
		arg_num = 0;
		while (cmd->args[arg_num])
			arg_num++;
		cmd->args = ft_arradd_str_mod(cmd->args, arg, arg_num);
		while (ft_isspace(ln[*i]))
			(*i)++;
		*start = *i;
	}
}

static int	parse_redirects(char **line, t_cmd *tmp, int *i, t_rl *rl)
{
	int	res;

	res = 1;
	while ((*line)[*i])
	{
		if (!ft_isspace((*line)[*i]))
		{
			if (non_valid_redirect(*line))
				res = -1;
			else if ((*line)[*i] == '>')
				*line = redirect_output(line, i, tmp, rl);
			else if ((*line)[*i] == '<')
				*line = redirect_input(line, i, tmp, rl);
			if (!*line)
				res = -2;
			if (res < 0)
				break ;
		}
		if ((*line)[*i] || *i < 0)
			(*i)++;
	}
	return (res);
}

static int	parse_symbols(char **ln, t_rl *rl, t_cmd *cmd, int *res)
{
	int	i;
	int	start;

	i = 0;
	while (ft_isspace((*ln)[i]))
		i++;
	start = i;
	while ((*ln)[i])
	{
		handle_basic_tokens(ln, &i, rl);
		if ((*ln)[i] == '<' && (*ln)[i + 1] && (*ln)[i + 1] == '<')
			*ln = heredoc(ln, &i, cmd, rl);
		if ((*ln)[i] == '>' || (*ln)[i] == '<')
			*res = parse_redirects(ln, cmd, &i, rl);
		if (*res < 0)
			return (*res);
		if ((*ln)[i] == '*')
			wildcard(*ln, &i, cmd, &start);
		if (!(*ln)[i] && start >= i)
			break ;
		retrieve_next_arg(*ln, cmd, &start, &i);
	}
	return (*res);
}

int	parser(char *command_line, t_rl *rl, t_cmd ***cmd)
{
	int		i;
	int		r;
	char	*line;
	t_cmd	*tmp;

	r = preparser(command_line);
	if (r <= 0)
		return (r);
	i = 0;
	while (!i || command_line[i - 1] == '|')
	{
		tmp = new_cmd();
		tmp->len = find_end(&command_line[i]);
		line = ft_substr(command_line, i, tmp->len);
		if ((is_line_empty(line, &r) || parse_symbols(&line, rl, tmp, &r) < 0)
			&& free_cmd(tmp))
			return (r);
		if (command_line[i + tmp->len] == '|')
			tmp->len++;
		i += tmp->len;
		retrieve_flags(tmp);
		free(line);
		*cmd = ft_arrcmd_addelem(*cmd, tmp);
	}
	return (r);
}

//int count_sumlen(t_cmd **cmd)
//{
//	int count;
//	int i;
//
//	count = 0;
//	i = -1;
//	while (cmd[++i])
//		count += cmd[i]->len;
//	return count;
//}
//
//int	main(int argc, char **argv, char **env)
//{
//	t_cmd	**cmd;
//	int len = 0;
//	int res;
//
//	t_rl *rl = malloc(sizeof(t_rl));
//	rl->env = env;
//	rl->mode = malloc(sizeof(int) * 2);
//	rl->mode[0] = 0;
//	rl->mode[1] = 0;
//	rl->mode_count = 0;
//	rl->status = 0;
//
//	char *case0 = "   ;";
//	char *case1 = "echo co'mma'nd\"000\"\"00\\$00\"'brbrbr'";
//	char *case2 = "echo 12345\" я $USER	\"123 ; \";\" ls ;";
//	char *case3 = "echo $USER";
//	char *case4 = "ls -l -a arg1 arg2 ' ' \" ' \" arg3";
//	char *case5 = "echo \"$USER\"";
//	char *case6 = "echo -n $USER $USER";
//	char *case7 = "echo test > 1";
//	char *case8 = "echo test >&0";
//	char *case9 = "cat 1 < 2 >&1";
//	char *case10 = "cat < 1 < 1 < 1 < 1";
//	char *case11 = "cat > 2\\>2";
//	char *case12 = "cat > $USER";
//	char *case13 = "echo > $USER";
//	char *case14 = "cat < 1";
//	char *case15 = "> 1 > 2";
//	char *case16 = "ls | ls | cat -e";
//	char *case17 = "ls | cat -e | grep 1 ; cd parser";
//	char *case18 = "\'\\\"$USER\'";
//	char *case19 = "echo test ; echo test1 ;   echo test2";
//	char *case20 = "echo $?";
//	char *case21 = "echo \\\"$USER\\\"\\\"";
//	char *case22 = "echo \\\"\\\"";
//	char *case23 = "echo < 123";
//	char *case24 = "ls > 1 > 2 > 3 > $USER | cat < $USER";
//	char *case25 = "ls|ls|ls";
//	char *case26 = "ls> 1 ; cat 1 ; rm 1";
//	char *case27 = "<<\xff";
//	char *case28 = "";
//
//	// ---------------
//	char *case30 = "cat <<asd\n\xff; cat <<$USER\n\xff";
//
//	char *mainCase = case28;
//	while (mainCase[len]) {
//		if (cmd)
//			free_arrcmd(cmd);
//		cmd = (t_cmd **)malloc(sizeof(cmd));
//		*cmd = NULL;
//		printf("%s\n", &mainCase[len]);
//		printf("%d\n", (res = parser(&mainCase[len], rl, &cmd)));
//		if (res < 0)
//		{
//			if (cmd)
//				free_arrcmd(cmd);
//			return (0);
//		}
//		len += count_sumlen(cmd);
//		if (mainCase[len])
//			len++;
//		int i = -1;
//		while (cmd[++i])
//		{
//			printf("Element %d\n", i);
//			int j = -1;
//			while (cmd[i]->args[++j])
//				printf("arg[%d] = %s$\n", j, cmd[i]->args[j]);
//			if (cmd[i]->flags)
//				printf("flags = %s\n", cmd[i]->flags);
//			printf("fd_from = %d\n", cmd[i]->fd_from);
//			printf("fd_to = %d\n", cmd[i]->fd_to);
//		}
//	}
//	if (cmd)
//		free_arrcmd(cmd);
//	while (1)
//		;
//}
