#include "../../includes/readterm.h"

void	wordend(t_rl *rl, int k, int end)
{
	int		check;
	char	ch;

	check = 0;
	while (k < rl->count_symb)
	{
		ch = rl->command_line[k - rl->plen];
		if (ft_isalnum(ch))
			check = 1;
		if (!ft_isalnum(ch) && check == 1)
		{
			check = 0;
			end = k;
			break ;
		}
		k++;
	}
	if (rl->cursor_pos < end)
	{
		tputs(tgoto(tgetstr("RI", 0), 0, end - rl->cursor_pos), 1, ft_putint);
		rl->cursor_pos = end;
	}
}
