#include "../includes/readterm.h"

void	casecore(t_rl *rl, t_node **histnode)
{
	while (ft_strcmp(rl->buf, "\n") && ft_strcmp(rl->buf, "\3")
			&& (ft_strcmp(rl->buf, "\4") || rl->command_line[0] != 0))
	{
		correct_rl(rl);
		read(0, rl->buf, BUF_SIZE);
		if (!ft_strcmp(rl->buf, "\e[A"))
			previous_cmd(rl, histnode);
		else if (!ft_strcmp(rl->buf, "\e[B"))
			next_cmd(rl, histnode);
		else if (!ft_strcmp(rl->buf, "\3"))
			sig_c(rl);
		else if (!ft_strcmp(rl->buf, "\t"))
			tabkey(rl);
		else if (!ft_strcmp(rl->buf, "\177"))
			delchar(rl);
		else if (!ft_strcmp(rl->buf, "\e[D"))
			left(rl);
		else if (!ft_strcmp(rl->buf, "\e[C"))
			right(rl);
		else if (!ft_strcmp(rl->buf, "\eb") || !ft_strcmp(rl->buf, "\e[1;5D"))
			wordbegin(rl);
		else if (!ft_strcmp(rl->buf, "\ef") || !ft_strcmp(rl->buf, "\e[1;5C"))
			wordend(rl);
		else if (!ft_strcmp(rl->buf, "\1") || !ft_strcmp(rl->buf, "\e[H"))
			home(rl);
		else if (!ft_strcmp(rl->buf, "\5") || !ft_strcmp(rl->buf, "\e[F"))
			end(rl);
		else if (rl->buf[0] == '\n')
			write (1, rl->buf, 1);
		else if ((!ft_isprint(rl->buf[0]) || rl->buf[1] != 0) && rl->buf[0] != '\4'
				&& rl->buf[0] != '\3' && rl->buf[0] != -47 && rl->buf[0] != -48)
			clear_buf(rl->buf, BUF_SIZE);
		else if (rl->cursor_pos < rl->count_symb)
			addchar(rl);
		else
			showchar(rl);
	}
}

int		*ft_arradd_int(int	*arr, int size, int	val)
{
	int *tmp;

	if (!arr)
	{
		arr = malloc(sizeof(int));
		arr[0] = val;
		return (arr);
	}
	else
	{
		tmp = malloc(sizeof(int) * (size));
		tmp[--size] = val;
		while (--size >= 0)
			tmp[size] = arr[size];
		free(arr);
		return (tmp);
	}
}

void	readterm(t_rl *rl, t_node **histnode)
{
	casecore(rl, histnode);
	add_rus(rl);
	writehist(rl);
	int i = 1;
	int z = 0;
	char	*bufstr;

	bufstr = ft_strdup(rl->command_line);
	while (bufstr[i])
	{
		if (bufstr[i] == '<' && bufstr[i - 1] == '<')
		{
			int end;

			end = ++i;
			while (bufstr[end] && ft_isspace(bufstr[end]))
				end++;
			while (bufstr[end] && !ft_isspace(bufstr[end]) && !ft_strchr(";|<>", bufstr[end]))
				end++;
			while (bufstr[end] && ft_isspace(bufstr[end]))
				end++;
			char *stoper;
			char *tail;

			tail = ft_substr(bufstr, end, ft_strlen(bufstr) - end);
			stoper = ft_substr((const char *)bufstr, i, end - i);
			stoper = ft_strtrim(stoper, " \t");
			if ((stoper[0] == '\'' || stoper [0] == '\"') 
				&& (stoper[ft_strlen(stoper) - 1] == '\'' || stoper [ft_strlen(stoper) - 1] == '\"'))
			{
				stoper = ft_strtrim(stoper, "\'\"");
				rl->mode = ft_arradd_int(rl->mode, ++z, 1);
			}
			else
				rl->mode = ft_arradd_int(rl->mode, ++z, 0);
			bufstr[i] = 0;
			//printf("beg=%d end=%d |%s|\nbufstr=%s|\ntail=|%s|\n", i, end, stoper, bufstr, tail);
			clear_buf(rl->command_line, rl->len);			
			while (ft_strcmp(rl->command_line, stoper) && ft_strcmp(rl->buf, "\3")
				&& (ft_strcmp(rl->buf, "\4") || rl->command_line[0] != 0))
			{
				rl->plen = 2;
				rl->cursor_pos = rl->plen;
				rl->count_symb = rl->plen;
				write (1, "> ", rl->plen);
				tputs(tgetstr("sc", 0), 1, ft_putint);
				clear_buf(rl->command_line, rl->len);
				clear_buf(rl->buf, BUF_SIZE);
				casecore(rl, histnode);
				if (ft_strcmp(rl->command_line, stoper))
				{
					bufstr = ft_strjoin(bufstr, rl->command_line);
					bufstr = ft_strjoin(bufstr, "\n");
					i += ft_strlen(rl->command_line) + 1;
				}
			}
			char *tmp;

			tmp = malloc(2);
			tmp[0] = -1;
			tmp[1] = 0;
			bufstr = ft_strjoin(bufstr, tmp);
			bufstr = ft_strjoin(bufstr, tail);
			free(tmp);
			free(tail);
			free(stoper);
		}
		if (bufstr[i] == '*' && bufstr[i + 1] == '*')
		{
			ft_strcpy(&bufstr[i], &bufstr[i + 1]);
			i--;
		}
		i++;
	}
	if (rl->len < ft_strlen(bufstr))
	{
		free(rl->command_line);
		rl->command_line = bufstr;
		rl->len = ft_strlen(rl->command_line);
	}
	else
	{
		clear_buf(rl->command_line, rl->len);
		ft_strcpy(rl->command_line, bufstr);
		free(bufstr);
	}
}
