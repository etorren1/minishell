#include "../../includes/readterm.h"

void	wordbegin(t_rl *rl)
{
	int		k = 0;
	int		beg = 0;
	int		check = 0;;
	char	ch;

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
		tputs(tgoto(tgetstr("RI", 0), 0, beg + rl->plen - rl->cursor_pos), 1, ft_putint);
		rl->cursor_pos = beg + rl->plen;
	}
}
