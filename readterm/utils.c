#include "../includes/readterm.h"

int	ft_putint(int ch)
{
	write (1, &ch, 1);
	return (1);
}

void	clear_buf(char *buf, int size)
{
	int	i;

	i = 0;
	while (i < size)
		buf[i++] = 0;
}
