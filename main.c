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
#define	MINISHELL	"\033[1;32mminishell-0.4$ \033[0m"
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

int	read_history(int fd, t_node **node)
{
	int		i;
	int		rd;
	char	*line;

	i = 0;
	while ((rd = get_next_line(fd, &line)) > 0)
	{
		ft_nodeadd_back(node, ft_nodenew(line));
		i++;
	}
	rd = get_next_line(fd, &line);
	ft_nodeadd_back(node, ft_nodenew(line));
	if (*node)
		*node = ft_nodelast(*node);
	else
		*node = ft_nodenew("\n");
	i++;
	if (rd == -1)
		return (-1);
	return (i);
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
	struct	termios saveterm;
	t_node	*histnode;
	int		len;
	int		i;
	int		fd;
	int		count_symb;
	int		cursor_pos;
	char	*command_line;
	char	*last_insert;
	char	*buf;
	char	**env;
	char	*history;
	char *ptr;

	ptr = NULL;
	histnode = NULL;
	history = ft_strjoin(get_absolute_path_process(argv[0]), HISTORY);
	env = malloc(sizeof(envp) * (ft_arrsize(envp) + 1));
	ft_arrcpy(env, envp);

	t_cmd *cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	tcgetattr(0, &saveterm);
	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON|ECHO);
	tcsetattr(0, TCSANOW, &term);

	tgetent(0, "xterm-256color");

	fd = open(history, O_RDWR | O_CREAT, 0777);
	len = 512;
	read_history(fd, &histnode);
	buf = (char *)malloc(BUF_SIZE);
	clear_buf(buf, BUF_SIZE);
	command_line = (char *)malloc(len);
	while (ft_strcmp(buf, "\4"))
	{
		cursor_pos = PROMPT;
		count_symb = PROMPT;
		last_insert = NULL;
		write (1, MINISHELL, PROMPT);
		tputs(tgetstr("sc", 0), 1, ft_putint);
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
				if (histnode->prev)
				{
					if (!histnode->next)
					{
						last_insert = malloc(ft_strlen(command_line));
						ft_strcpy(last_insert, command_line);
					}
					else
					{
						free(histnode->content);
						histnode->content = ft_strdup(command_line);
					}
					histnode = histnode->prev;
					clear_buf(command_line, len);
					tputs(tgetstr("rc", 0), 1, ft_putint);
					tputs(tgetstr("ce", 0), 1, ft_putint);
					ft_strcpy(command_line, histnode->content);
					cursor_pos = ft_strlen(command_line) + PROMPT;
					count_symb = ft_strlen(command_line) + PROMPT;
					write (1, command_line, ft_strlen(command_line));
				}
			}
				// key_down for output next command
			else if (!ft_strcmp(buf, "\e[B"))
			{
				if (histnode->next)
				{
					free(histnode->content);
					histnode->content = ft_strdup(command_line);
					histnode = histnode->next;
					clear_buf(command_line, len);
					tputs(tgetstr("rc", 0), 1, ft_putint);
					tputs(tgetstr("ce", 0), 1, ft_putint);
					if (!histnode->next)
						ft_strcpy(command_line, last_insert);
					else
						ft_strcpy(command_line, histnode->content);
					cursor_pos = ft_strlen(command_line) + PROMPT;
					count_symb = ft_strlen(command_line) + PROMPT;
					write (1, command_line, ft_strlen(command_line));
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
				write (1, buf, i);
				// another keys catch (debug feature)
			else if (buf[0] == -47 || buf[0] == -48)
			{
				printf(" \033[31mWarning:\033[0m Choose an English keyboard layout\n");
			}
			else if ((!ft_isprint(buf[0]) || buf[1] != 0) && buf[0] != '\4')
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
				command_line[cursor_pos - PROMPT] = buf[0];
				cursor_pos += write (1, buf, i);
			}
		}
		if (ft_strcmp(buf, "\4"))
		{
			if (last_insert)
				free(last_insert);
			histnode = ft_nodelast(histnode);
			histnode = histnode->prev;
			command_line[count_symb - PROMPT] = 0;
			if (ft_strcmp(histnode->content, command_line))
			{
				histnode = histnode->next;
				free(histnode->content);
				histnode->content = ft_strdup(command_line);
				ft_nodeadd_back(&histnode, ft_nodenew(ft_strdup("\n")));
				write(fd, command_line, ft_strlen(command_line));
				write(fd, "\n", 1);
				histnode = histnode->next;
			}
			else
				histnode = histnode->next;
			cmd->args = malloc(sizeof (char *));
			*cmd->args = NULL;
			cmd->flags = NULL;
			int i = 0;
			while (command_line[i]) {
				parser(&command_line[i], env, cmd);
				processor(cmd, &env);
				i += cmd->len + 1;
			}
		}
	}
	close(fd);
	fd = open(history, O_WRONLY | O_TRUNC, 0777);
	histnode = ft_nodefirst(histnode);
	while (histnode->next)
	{
		write(fd, histnode->content, ft_strlen(histnode->content));
		write(fd, "\n", 1);
		histnode = histnode->next;
	}
	write (1, "exit\n", 5);
	free(history);
	free(command_line);
	ft_arrfree(env);
	close (fd);

	tcsetattr(0, TCSANOW, &saveterm);
	return (0);
}
