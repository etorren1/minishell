#include "../../includes/readterm.h"

int	read_history(int fd, t_node **node)
{
	int		i;
	int		rd;
	char	*line;

	i = 0;
	line = NULL;
	rd = get_next_line(fd, &line);
	while (rd > 0)
	{
		ft_nodeadd_back(node, ft_nodenew(line));
		rd = get_next_line(fd, &line);
		i++;
	}
	if (line)
		free(line);
	rd = get_next_line(fd, &line);
	ft_nodeadd_back(node, ft_nodenew(line));
	if (ft_nodesize(*node) == 1)
		ft_nodeadd_back(node, ft_nodenew(ft_strdup("\n")));
	*node = ft_nodelast(*node);
	i++;
	if (rd == -1)
		return (-1);
	return (i);
}
