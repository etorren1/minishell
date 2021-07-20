#include "../../includes/readterm.h"

void	previous_cmd(t_rl *rl, t_node **histnode)
{
	if ((*histnode)->prev)
	{
		if (!(*histnode)->next)
		{
			rl->last_insert = malloc(ft_strlen(rl->command_line));
			ft_strcpy(rl->last_insert, rl->command_line);
		}
		else
		{
			free((*histnode)->content);
			(*histnode)->content = ft_strdup(rl->command_line);
		}
		(*histnode) = (*histnode)->prev;
		clear_buf(rl->command_line, rl->len);
		tputs(tgetstr("rc", 0), 1, ft_putint);
		tputs(tgetstr("ce", 0), 1, ft_putint);
		while ((int)ft_strlen((*histnode)->content) > rl->len)
			mem_add(rl);
		ft_strcpy(rl->command_line, (*histnode)->content);
		rl->cursor_pos = ft_strlen(rl->command_line) + rl->plen;
		rl->count_symb = rl->cursor_pos;
		write (1, rl->command_line, ft_strlen(rl->command_line));
	}
}
