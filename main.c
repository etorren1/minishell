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

#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <term.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#define MINISHELL	15
#define	BUF_SIZE	12

/*
*	Insert mode have bugs. It print odd symbols
*	Ctrl + key_left/right have bugs. It print odd symbols
*/

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
	tail = malloc(ft_strlen(&(*str)[i - MINISHELL]) + 1);
	ft_strcpy(tail, &(*str)[i - MINISHELL]);
	(*str)[(i++) - MINISHELL] = ch;
	while (tail[j])
		(*str)[(i++) - MINISHELL] = tail[j++];
	free(tail);
}

void	ft_delchar(char **str, int i)
{
	char	*tail;
	int	 j;

	j = 0;
	tail = malloc(ft_strlen(&(*str)[i - MINISHELL]) + 1);
	ft_strcpy(tail, &(*str)[(i--) - MINISHELL]);
	while (tail[j])
		(*str)[(i++) - MINISHELL] = tail[j++];
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
			str = ft_realloc(str, size);
			size += size;
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

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
//	term.c_cc[VMIN] = 1;
//	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);

	tgetent(0, "xterm-256color");

	fd = open(".minishell_history", O_RDWR | O_CREAT, 0777);
	len = 1024;
	count_lines = history_line_count(fd);
	buf = (char *)malloc(BUF_SIZE);
	command_line = (char *)malloc(len);
	while (ft_strcmp(buf, "\4"))
	{
		cursor_pos = MINISHELL;
		count_symb = MINISHELL;
		last_insert = NULL;
		write (1, "minishell-0.1$ ", MINISHELL);
		tputs(save_cursor, 1, ft_putint);
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
				tmpfd = open(".minishell_history", O_RDONLY);
				tmp = get_history_line(tmpfd, current_line);
				tputs(restore_cursor, 1, ft_putint);
				tputs(tgetstr("ce", 0), 1, ft_putint);
				ft_strcpy(command_line, tmp);
				cursor_pos = ft_strlen(command_line) + MINISHELL;
				count_symb = ft_strlen(command_line) + MINISHELL;
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
					tmpfd = open(".minishell_history", O_RDONLY);
					tmp = get_history_line(tmpfd, current_line);
					tputs(restore_cursor, 1, ft_putint);
					tputs(tgetstr("ce", 0), 1, ft_putint);
					if (current_line == count_lines)
						ft_strcpy(command_line, last_insert);
					else
						ft_strcpy(command_line, tmp);
					cursor_pos = ft_strlen(command_line) + MINISHELL;
					count_symb = ft_strlen(command_line) + MINISHELL;
					write (1, command_line, ft_strlen(command_line));
					free (tmp);
					close(tmpfd);
				}
			}
			// key_backspace for delite character
			else if (!ft_strcmp(buf, "\177"))
			{
				if (cursor_pos > MINISHELL)
				{
					ft_delchar(&command_line, cursor_pos);
					cursor_pos--;
					count_symb--;
					tputs(cursor_left, 1, ft_putint);
					tputs(tgetstr("dc", 0), 1, ft_putint);
				}
			}
			// key_left
			else if (!ft_strcmp(buf, "\e[D"))
			{
				if (cursor_pos > MINISHELL)
				{
					cursor_pos--;
					tputs(cursor_left, 1, ft_putint);
				}
			}
			// key_right
			else if (!ft_strcmp(buf, "\e[C"))
			{
				if (count_symb > cursor_pos)
				{
					cursor_pos++;
					tputs(cursor_right, 1, ft_putint);
				}
			}
			// ctrl + key_left move directly by word towards
			else if (!ft_strcmp(buf, "\e[1;5D"))
			{
				int		k = 0;
				int		beg = 0;
				int		check = 0;;
				char	ch;

				while (k < cursor_pos - MINISHELL)
				{
					ch = command_line[k];
					if (!ft_isalnum(ch) && !ft_isalpha(ch))
						check = 1;
					if ((ft_isalnum(ch) || ft_isalpha(ch)) && check == 1)
					{
						check = 0;
						beg = k;
					}
					k++;
				}
				tputs(restore_cursor, 1, ft_putint);
				cursor_pos = MINISHELL;
				while (cursor_pos < beg + MINISHELL)
				{
					tputs(cursor_right, 1, ft_putint);
					cursor_pos++;
				}
			}
			// ctrl + key_right move directly by word towards
			else if (!ft_strcmp(buf, "\e[1;5C"))
			{
				int		k = cursor_pos;
				int		end = count_symb;
				int		check = 0;;
				char	ch;

				while (k < count_symb)
				{
					ch = command_line[k - MINISHELL];
					if (ft_isalnum(ch) || ft_isalpha(ch))
						check = 1;
					if (!ft_isalnum(ch) && !ft_isalpha(ch) && check == 1)
					{
						check = 0;
						end = k;
						break;
					}
					k++;
				}
				while (cursor_pos < end)
				{
					tputs(cursor_right, 1, ft_putint);
					cursor_pos++;
				}
			}
			// key_home move cursor in begin command line
			else if (!ft_strcmp(buf, "\e[H"))
			{
				tputs(restore_cursor, 1, ft_putint);
				cursor_pos = MINISHELL;
			}
			// key_end move cursor in end command line
			else if (!ft_strcmp(buf, "\e[F"))
			{
				while (cursor_pos < count_symb)
				{
					tputs(cursor_right, 1, ft_putint);
					cursor_pos++;
				}
			}
			// add newline in command string
			else if (buf[0] == '\n')
			{
				command_line[count_symb - MINISHELL] = buf[0];
				command_line[1 + count_symb - MINISHELL] = '\0';
				write (1, buf, i);
			}
			// another keys catch (debug feature)
			else if (buf[1] != 0)
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
				command_line[cursor_pos - MINISHELL] = buf[0];
				cursor_pos += write (1, buf, i);
				command_line[cursor_pos - MINISHELL] = '\0';
			}
		}
		if (last_insert)
			free(last_insert);
		count_lines++;
		current_line = count_lines;
		write(fd, command_line, ft_strlen(command_line));
		//*
		// PARSER & LOGIC PART
		//*
	}
	write (1, "\n", 1);
	free(command_line);
	close (fd);
	return (0);
}
