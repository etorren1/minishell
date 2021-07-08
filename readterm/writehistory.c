#include "../includes/readterm.h"

void	writehist(t_rl *rl)
{
	if (rl->last_insert)
		free(rl->last_insert);
	rl->histnode = ft_nodelast(rl->histnode);
	rl->histnode = rl->histnode->prev;
	rl->command_line[rl->count_symb - PROMPT] = 0;
	if (ft_strcmp(rl->histnode->content, rl->command_line) && ft_strcmp("", rl->command_line))
	{
		rl->histnode = rl->histnode->next;
		free(rl->histnode->content);
		rl->histnode->content = ft_strdup(rl->command_line);
		ft_nodeadd_back(&rl->histnode, ft_nodenew(ft_strdup("\n")));
		write(rl->fd, rl->command_line, ft_strlen(rl->command_line));
		write(rl->fd, "\n", 1);
		rl->histnode = rl->histnode->next;
	}
	else
		rl->histnode = rl->histnode->next;
}
