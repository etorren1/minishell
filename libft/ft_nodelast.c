#include "libft.h"

t_node	*ft_nodelast(t_node *node)
{
	if (!node)
		return (0);
	while (node->next)
		node = node->next;
	return (node);
}
