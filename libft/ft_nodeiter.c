#include "libft.h"

void	ft_nodeiter(t_node *node, void (*f)(void *))
{
	while (node)
	{
		f(node->content);
		node = node->next;
	}
}
