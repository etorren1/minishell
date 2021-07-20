#include "../../includes/readterm.h"

void	ft_delchar(char **str, int i, int size, int len)
{
	char	*tail;
	int		j;

	j = 0;
	if (i == len + 1)
	{
		(*str)[0] = 0;
		return ;
	}
	else if (i == size)
		(*str)[i - len - 1] = 0;
	tail = malloc(ft_strlen(&(*str)[i - len]) + 1);
	ft_strcpy(tail, &(*str)[(i--) - len]);
	while (tail[j])
		(*str)[(i++) - len] = tail[j++];
	free(tail);
}

void	delchar(t_rl *rl)
{
	if (rl->cursor_pos > rl->plen)
	{
		ft_delchar(&rl->command_line, rl->cursor_pos,
			 rl->count_symb, rl->plen);
		rl->cursor_pos--;
		rl->count_symb--;
		tputs(tgetstr("le", 0), 1, ft_putint);
		tputs(tgetstr("dc", 0), 1, ft_putint);
	}
}
