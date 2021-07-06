#include "../../includes/readterm.h"

void	correct_rl(t_rl *rl)
{
	if (rl->count_symb < rl->cursor_pos)
		rl->count_symb = rl->cursor_pos;
	if (rl->count_symb >= rl->len + PROMPT)
	{
		rl->len += rl->len;
		rl->command_line = ft_realloc(rl->command_line, rl->len);
	}
	clear_buf(rl->buf, BUF_SIZE);
}
