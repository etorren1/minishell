#include "../includes/readterm.h"

void	preread(t_rl *rl, struct termios *term)
{
	term->c_lflag &= ~(ISIG|ICANON|ECHO); //ISIG
	tcsetattr(0, TCSANOW, term);
	rl->plen = PROMPT;
	rl->cursor_pos = rl->plen;
	rl->count_symb = rl->plen;
	rl->last_insert = NULL;	
	write (1, MINISHELL, rl->plen);
	tputs(tgetstr("sc", 0), 1, ft_putint);
	clear_buf(rl->command_line, rl->len);
	clear_buf(rl->buf, BUF_SIZE);
}
