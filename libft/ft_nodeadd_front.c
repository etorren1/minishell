#include "libft.h"

void	ft_nodeadd_front(t_node **node, t_node *new)
{
	new->next = *node;
	(*node)->prev = new;
	*node = new;
}
