#include "../includes/readterm.h"

void	readterm(t_rl *rl, t_node **histnode)
{
	while (ft_strcmp(rl->buf, "\n")
			&& (ft_strcmp(rl->buf, "\4") || rl->command_line[0] != 0))
	{
		correct_rl(rl);
		read(0, rl->buf, BUF_SIZE);
		if (!ft_strcmp(rl->buf, "\e[A"))
			previous_cmd(rl, histnode);
		else if (!ft_strcmp(rl->buf, "\e[B"))
			next_cmd(rl, histnode);
		else if (!ft_strcmp(rl->buf, "\t"))
			tabkey(rl);
		else if (!ft_strcmp(rl->buf, "\177"))
			delchar(rl);
		else if (!ft_strcmp(rl->buf, "\e[D"))
			left(rl);
		else if (!ft_strcmp(rl->buf, "\e[C"))
			right(rl);
		else if (!ft_strcmp(rl->buf, "\eb") || !ft_strcmp(rl->buf, "\e[1;5D"))
			wordbegin(rl);
		else if (!ft_strcmp(rl->buf, "\ef") || !ft_strcmp(rl->buf, "\e[1;5C"))
			wordend(rl);
		else if (!ft_strcmp(rl->buf, "\1") || !ft_strcmp(rl->buf, "\e[H"))
			home(rl);
		else if (!ft_strcmp(rl->buf, "\5") || !ft_strcmp(rl->buf, "\e[F"))
			end(rl);
		else if (rl->buf[0] == '\n')
			write (1, rl->buf, 1);
		// another keys catch (debug feature)
		else if (rl->buf[0] == -47 || rl->buf[0] == -48)
			printf(" \033[31mWarning:\033[0m Choose an English keyboard layout\n");
		else if ((!ft_isprint(rl->buf[0]) || rl->buf[1] != 0) && rl->buf[0] != '\4')
		{
			clear_buf(rl->buf, BUF_SIZE);
			//printf(" \033[31mWarning:\033[0m Non visible symbol\n");
		}
		else if (rl->cursor_pos < rl->count_symb)
			addchar(rl);
		else
			showchar(rl);
	}
}