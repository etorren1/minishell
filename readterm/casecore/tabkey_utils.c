#include "../../includes/readterm.h"

void	restore_line(t_rl *rl)
{
	tputs(tgetstr("do", 0), 1, ft_putint);
	write (1, MINISHELL, rl->plen);
	tputs(tgetstr("sc", 0), 1, ft_putint);
	ft_putstr_fd(rl->command_line, 1);
}
