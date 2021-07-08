#include "../includes/readterm.h"

void	preread(t_rl *rl, struct termios *term)
{
	term->c_lflag &= ~(ISIG|ICANON|ECHO);
	tcsetattr(0, TCSANOW, term);
	rl->cursor_pos = PROMPT;
	rl->count_symb = PROMPT;
	rl->last_insert = NULL;	
	write (1, MINISHELL, PROMPT);
	tputs(tgetstr("sc", 0), 1, ft_putint);
	clear_buf(rl->command_line, rl->len);
	clear_buf(rl->buf, BUF_SIZE);
}
