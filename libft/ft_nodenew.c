#include "libft.h"

t_node	*ft_nodenew(void *content)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (0);
	node->content = content;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
