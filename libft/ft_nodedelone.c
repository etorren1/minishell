#include "libft.h"

void	ft_nodedelone(t_node *node, void (*del)(void *))
{
	t_node	*temp;

	if (node && del)
	{
		del(node->content);
		temp = node;
		node = node->next;
		free(temp);
	}
}
