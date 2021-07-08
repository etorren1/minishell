#include "../../includes/readterm.h"

void	sig_c(t_rl *rl)
{
	write(1, "^C\n", 3);
	clear_buf(rl->command_line, rl->len);
}
