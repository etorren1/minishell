#include "libft.h"

void	ft_nodeclear(t_node **node, void (*del)(void *))
{
	t_node	*temp;

	temp = *node;
	if (!*node || !del)
		return ;
	while (*node)
	{
		temp = *node;
		del(temp->content);
		*node = temp->next;
		free(temp);
	}
}
