#include "../../includes/readterm.h"

void	showchar(t_rl *rl)
{
	if (rl->buf[0] != '\4')
	{
		rl->command_line[rl->cursor_pos - PROMPT] = rl->buf[0];
		rl->cursor_pos += write (1, rl->buf, ft_strlen(rl->buf));
	}
}
