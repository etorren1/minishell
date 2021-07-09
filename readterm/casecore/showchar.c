#include "../../includes/readterm.h"

void	showchar(t_rl *rl)
{
	if (rl->buf[0] != '\4')
	{
		rl->command_line[rl->cursor_pos - PROMPT] = rl->buf[0];
		if (rl->buf[0] == -47 || rl->buf[0] == -48)
			rl->command_line[rl->cursor_pos - PROMPT] = rl->buf[1];
		rl->cursor_pos++;
		write (1, rl->buf, ft_strlen(rl->buf));
	}
}
