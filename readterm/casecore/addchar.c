#include "../../includes/readterm.h"

void	ft_addchar(char **str, char ch, int i, int len)
{
	char	*tail;
	int		j;

	j = 0;
	tail = malloc(ft_strlen(&(*str)[i - len]) + 1);
	ft_strcpy(tail, &(*str)[i - len]);
	(*str)[(i++) - len] = ch;
	while (tail[j])
		(*str)[(i++) - len] = tail[j++];
	free(tail);
}

void	addchar(t_rl *rl)
{
	ft_addchar(&rl->command_line, rl->buf[0], rl->cursor_pos, rl->plen);
	tputs(tgetstr("im", 0), 1, ft_putint);
	rl->cursor_pos += write (1, rl->buf, ft_strlen(rl->buf));
	rl->count_symb++;
	tputs(tgetstr("ei", 0), 1, ft_putint);
}
