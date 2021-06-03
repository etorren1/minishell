#include "libft.h"

t_node	*ft_nodefirst(t_node *node)
{
	if (!node)
		return (0);
	while (node->prev)
		node = node->prev;
	return (node);
}
