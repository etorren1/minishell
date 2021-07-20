#include "../../includes/readterm.h"

void	left(t_rl *rl)
{
	if (rl->cursor_pos > rl->plen)
	{
		rl->cursor_pos--;
		tputs(tgetstr("le", 0), 1, ft_putint);
	}
}

void	right(t_rl *rl)
{
	if (rl->count_symb > rl->cursor_pos)
	{
		rl->cursor_pos++;
		tputs(tgetstr("nd", 0), 1, ft_putint);
	}
}

void	home(t_rl *rl)
{
	tputs(tgetstr("rc", 0), 1, ft_putint);
	rl->cursor_pos = rl->plen;
}

void	end(t_rl *rl)
{
	if (rl->cursor_pos < rl->count_symb)
	{
		tputs(tgoto(tgetstr("RI", 0), 0, rl->count_symb
				 - rl->cursor_pos), 1, ft_putint);
		rl->cursor_pos = rl->count_symb;
	}
}
