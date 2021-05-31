/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 11:21:53 by etorren           #+#    #+#             */
/*   Updated: 2021/05/16 19:00:15 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"
#include <term.h>
#include <termios.h>
#define	BUF_SIZE	12
#define PROMPT		26
#define	MINISHELL	"\033[1;32mminishell-0.3$ \033[0m"
#define HISTORY		".minishell_history"

int	ft_putint(int ch)
{
	write (1, &ch, 1);
	return (1);
}

void	ft_addchar(char **str, char ch, int i)
{
	char	*tail;
	int	 j;

	j = 0;
	tail = malloc(ft_strlen(&(*str)[i - PROMPT]) + 1);
	ft_strcpy(tail, &(*str)[i - PROMPT]);
	(*str)[(i++) - PROMPT] = ch;
	while (tail[j])
		(*str)[(i++) - PROMPT] = tail[j++];
	free(tail);
}

void	ft_delchar(char **str, int i)
{
	char	*tail;
	int	 j;

	j = 0;
	tail = malloc(ft_strlen(&(*str)[i - PROMPT]) + 1);
	ft_strcpy(tail, &(*str)[(i--) - PROMPT]);
	while (tail[j])
		(*str)[(i++) - PROMPT] = tail[j++];
	free(tail);
}

int	history_line_count(int fd)
{
	int		i;
	int		rd;
	char	ch;

	i = 0;
	while ((rd = read(fd, &ch, 1)) > 0)
		if (ch == '\n')
			i++;
	if (rd == -1)
		return (-1);
	return (i);
}

static void	get_line_pos(int fd, int pos)
{
	int		rd;
	char	ch;
	int		i;

	i = 0;
	while (i < pos)
	{
		read(fd, &ch, 1);
		if (ch == '\n')
			i++;
	}
}

char	*get_history_line(int fd, int pos)
{
	char	ch;
	size_t	i;
	size_t	size;
	char	*str;

	get_line_pos(fd, pos);
	i = 0;
	size = 1024;
	str = (char *)malloc(size);
	while (read(fd, &ch, 1) > 0 && ch != '\n')
	{
		str[i++] = ch;
		if (i > size)
		{
			size += size;
			str = ft_realloc(str, size);
		}
	}
	str[i] = '\0';
	return (str);
}

void	clear_buf(char *buf, int size)
{
	int i;

	i = 0;
	while (i < size)
		buf[i++] = 0;
}

int	main(int argc, char **argv, char **envp)
{
	struct	termios term;
	int		len;
	int		i;
	int		fd;
	int		count_symb;
	int		cursor_pos;
	int		count_lines;
	int		current_line;
	char	*command_line;
	char	*last_insert;
	char	*buf;
	char	**env;
	char	*history;
	char *ptr;

	ptr = NULL;
	history = ft_strjoin(get_absolute_path_process(argv[0]), HISTORY);
	env = malloc(sizeof(envp) * (ft_arrsize(envp) + 1));
	ft_arrcpy(env, envp);

	t_cmd *cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);

	tgetent(0, "xterm-256color");

	fd = open(history, O_RDWR | O_CREAT, 0777);
	len = 1024;
	count_lines = history_line_count(fd);
	buf = (char *)malloc(BUF_SIZE);
	command_line = (char *)malloc(len);
	while (ft_strcmp(buf, "\4"))
	{
		cursor_pos = PROMPT;
		count_symb = PROMPT;
		last_insert = NULL;
		write (1, MINISHELL, PROMPT);
		tputs(tgetstr("sc", 0), 1, ft_putint);
		current_line = count_lines;
		clear_buf(command_line, len);
		clear_buf(buf, BUF_SIZE);
		while (ft_strcmp(buf, "\n") && ft_strcmp(buf, "\4"))
		{
			if (count_symb < cursor_pos)
				count_symb = cursor_pos;
			if (count_symb > len)
			{
				len += len;
				command_line = ft_realloc(command_line, len);
			}
			clear_buf(buf, BUF_SIZE);
			i = read(0, buf, BUF_SIZE);
			// key_up for output previous command
			if (!ft_strcmp(buf, "\e[A"))
			{
				char *tmp;
				int k = 0;
				int tmpfd;

				if (current_line == count_lines)
				{
					last_insert = malloc(ft_strlen(command_line));
					ft_strcpy(last_insert, command_line);
				}
				if (current_line > 0)
					current_line--;
				tmpfd = open(history, O_RDONLY);
				tmp = get_history_line(tmpfd, current_line);
				tputs(tgetstr("rc", 0), 1, ft_putint);
				tputs(tgetstr("ce", 0), 1, ft_putint);
				ft_strcpy(command_line, tmp);
				cursor_pos = ft_strlen(command_line) + PROMPT;
				count_symb = ft_strlen(command_line) + PROMPT;
				write (1, command_line, ft_strlen(command_line));
				free (tmp);
				close(tmpfd);
			}
				// key_down for output next command
			else if (!ft_strcmp(buf, "\e[B"))
			{
				char *tmp;
				int k = 0;
				int tmpfd;

				if (current_line < count_lines)
				{
					current_line++;
					tmpfd = open(history, O_RDONLY);
					tmp = get_history_line(tmpfd, current_line);
					tputs(tgetstr("rc", 0), 1, ft_putint);
					tputs(tgetstr("ce", 0), 1, ft_putint);
					if (current_line == count_lines)
						ft_strcpy(command_line, last_insert);
					else
						ft_strcpy(command_line, tmp);
					cursor_pos = ft_strlen(command_line) + PROMPT;
					count_symb = ft_strlen(command_line) + PROMPT;
					write (1, command_line, ft_strlen(command_line));
					free (tmp);
					close(tmpfd);
				}
			}
				// key_backspace for delite character
			else if (!ft_strcmp(buf, "\177"))
			{
				if (cursor_pos > PROMPT)
				{
					ft_delchar(&command_line, cursor_pos);
					cursor_pos--;
					count_symb--;
					tputs(tgetstr("le", 0), 1, ft_putint);
					tputs(tgetstr("dc", 0), 1, ft_putint);
				}
			}
				// key_left
			else if (!ft_strcmp(buf, "\e[D"))
			{
				if (cursor_pos > PROMPT)
				{
					cursor_pos--;
					tputs(tgetstr("le", 0), 1, ft_putint);
				}
			}
				// key_right
			else if (!ft_strcmp(buf, "\e[C"))
			{
				if (count_symb > cursor_pos)
				{
					cursor_pos++;
					tputs(tgetstr("nd", 0), 1, ft_putint);
				}
			}
				// ctrl + key_left move directly by word towards // "\e[1;5D" for linux / "\eb" for macos
			else if (!ft_strcmp(buf, "\eb") || !ft_strcmp(buf, "\e[1;5D"))
			{
				int		k = 0;
				int		beg = 0;
				int		check = 0;;
				char	ch;

				while (k < cursor_pos - PROMPT)
				{
					ch = command_line[k];
					if (!ft_isalnum(ch))
						check = 1;
					if (ft_isalnum(ch) && check == 1)
					{
						check = 0;
						beg = k;
					}
					k++;
				}
				tputs(tgetstr("rc", 0), 1, ft_putint);
				cursor_pos = PROMPT;
				if (cursor_pos < beg + PROMPT)
				{
					tputs(tgoto(tgetstr("RI", 0), 0, beg + PROMPT - cursor_pos), 1, ft_putint);
					cursor_pos = beg + PROMPT;
				}
			}
			// ctrl + key_right move directly by word towards // "\e[1;5C" for linux / "\ef" for macos
			else if (!ft_strcmp(buf, "\ef") || !ft_strcmp(buf, "\e[1;5C"))
			{
				int		k = cursor_pos;
				int		end = count_symb;
				int		check = 0;;
				char	ch;

				while (k < count_symb)
				{
					ch = command_line[k - PROMPT];
					if (ft_isalnum(ch))
						check = 1;
					if (!ft_isalnum(ch) && check == 1)
					{
						check = 0;
						end = k;
						break;
					}
					k++;
				}
				if (cursor_pos < end)
				{
					tputs(tgoto(tgetstr("RI", 0), 0, end - cursor_pos), 1, ft_putint);
					cursor_pos = end;
				}
			}
				// key_home move cursor in begin command // line "\e[H" for linux or fn + key_left on macos  / "\1" for macos
			else if (!ft_strcmp(buf, "\1") || !ft_strcmp(buf, "\e[H"))
			{
				tputs(tgetstr("rc", 0), 1, ft_putint);
				cursor_pos = PROMPT;
			}
				// key_end move cursor in end command line // "\e[F" for linux or fn + key_rignt on macos / "\5" for macos
			else if (!ft_strcmp(buf, "\5") || !ft_strcmp(buf, "\e[F"))
			{
				if (cursor_pos < count_symb)
				{
					tputs(tgoto(tgetstr("RI", 0), 0, count_symb - cursor_pos), 1, ft_putint);
					cursor_pos = count_symb;
				}
			}
				// add newline in command string
			else if (buf[0] == '\n')
			{
				command_line[count_symb - PROMPT] = buf[0];
				command_line[1 + count_symb - PROMPT] = '\0';
				write (1, buf, i);
			}
				// another keys catch (debug feature)
			else if (buf[0] == -47 || buf[0] == -48)
			{
				printf(" \033[31mWarning:\033[0m Choose an English keyboard layout\n");
			}
			else if (!ft_isprint(buf[0]) || buf[1] != 0)
			{
				printf(" \033[31mWarning:\033[0m Non visible symbol\n");
			}
				// insert mode, command line edit
			else if (cursor_pos < count_symb)
			{
				ft_addchar(&command_line, buf[0], cursor_pos);
				tputs(tgetstr("im", 0), 1, ft_putint);
				cursor_pos += write (1, buf, 1 );
				count_symb++;
				tputs(tgetstr("ei", 0), 1, ft_putint);
			}
				// standart output characters from user
			else
			{
				if (buf[0] != '\n')
					command_line[cursor_pos - PROMPT] = buf[0];
				cursor_pos += write (1, buf, i);
			}
		}
		if (last_insert)
			free(last_insert);
		int k = 1;
		if (ptr)
			k = ft_strcmp(ptr, command_line);
		if (k != 0) {
			count_lines++;
			current_line = count_lines;
			write(fd, command_line, ft_strlen(command_line));
		}
		if (ptr)
			free(ptr);
		ptr = ft_strdup(command_line);
		//*
		// PARSER & LOGIC PART
		i = 0;
		simple_parser(&command_line[i], cmd);
		/*int l = 0;
		printf("\n-------PARSER--------\n");
		printf("type = %s\nflags = %s\nlen = %d\n", cmd->type, cmd->flags, cmd->len);
		while (l < cmd->count_args)
		{
			printf("args[%d] = %s\n", l, cmd->args[l]);
			l++;
		}*/
		processor(cmd, &env);
		/*int p = 0;
		printf("\e[31m-----ENV-----\n");
		while (env[p])
			printf("%s\n", env[p++]);
		printf("\e[0m\n");
		p = 0;
		envp = env;
		printf("\e[33m-----ENVP-----\n");
		while (envp[p])
			printf("%s\n", envp[p++]);
		printf("\e[0m\n");
		printf("%s\n", getenv("HOME"));*/
		/*
		i = 0;
		int l = 0;
		while (simple_parser(&command_line[i], cmd) > 0)
		{
		//	simple_parser(&command_line[i], cmd);
			printf("\n-------PARSER--------\n");
			printf("type = %s\nflags = %s\nlen = %d\n", cmd->type, cmd->flags, cmd->len);
			while (l < cmd->count_args)
			{
				printf("args[%d] = %s\n", l, cmd->args[l]);
				l++;
			}
			i += cmd->len;
		}
		printf("\n-------PARSER--------\n");
		printf("type = %s\nflags = %s\nlen = %d\n", cmd->type, cmd->flags, cmd->len);
		while (l < cmd->count_args)
		{
			printf("args[%d] = %s\n", l, cmd->args[l]);
			l++;
		}
		i += cmd->len;*/
		//*
	}
	write (1, "\n", 1);
	free(history);
	free(command_line);
	ft_arrfree(env);
	close (fd);
	return (0);
}
