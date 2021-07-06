#include "../../includes/readterm.h"

void	ft_delchar(char **str, int i, int size)
{
	char	*tail;
	int	 j;

	j = 0;
	if (i == PROMPT + 1)
	{
		(*str)[0] = 0;
		return ;
	}
	else if (i == size)
		(*str)[i - PROMPT - 1] = 0;
	tail = malloc(ft_strlen(&(*str)[i - PROMPT]) + 1);
	ft_strcpy(tail, &(*str)[(i--) - PROMPT]);
	while (tail[j])
		(*str)[(i++) - PROMPT] = tail[j++];
	free(tail);
}

void    delchar(t_rl *rl)
{
    if (rl->cursor_pos > PROMPT)
    {
        ft_delchar(&rl->command_line, rl->cursor_pos, rl->count_symb);
        rl->cursor_pos--;
        rl->count_symb--;
        tputs(tgetstr("le", 0), 1, ft_putint);
        tputs(tgetstr("dc", 0), 1, ft_putint);
    }
}
