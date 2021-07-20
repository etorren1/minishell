#include "../includes/minishell.h"

void	mem_add(t_rl *rl)
{
	rl->len += rl->len;
	rl->command_line = ft_realloc(rl->command_line, rl->len);
}
