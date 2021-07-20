#include "../../includes/readterm.h"

void	wordbegin(t_rl *rl, int k, int beg)
{
	int		check;
	char	ch;

	check = 0;
	while (k < rl->cursor_pos - rl->plen)
	{
		ch = rl->command_line[k];
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
	rl->cursor_pos = rl->plen;
	if (rl->cursor_pos < beg + rl->plen)
	{
		tputs(tgoto(tgetstr("RI", 0), 0, beg + rl->plen
				 - rl->cursor_pos), 1, ft_putint);
		rl->cursor_pos = beg + rl->plen;
	}
}
