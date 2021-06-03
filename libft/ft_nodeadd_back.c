#include "libft.h"

void	ft_nodeadd_back(t_node **node, t_node *new)
{
	t_node	*temp;

	temp = *node;
	if (temp)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
	else
		*node = new;
}
