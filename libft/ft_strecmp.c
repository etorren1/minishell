#include "libft.h"

int	ft_strecmp(const char *str, const char *tail)
{
	unsigned char	*tmp1;
	unsigned char	*tmp2;
	size_t			i;
	size_t			j;

	tmp1 = (unsigned char *)str;
	tmp2 = (unsigned char *)tail;
	if (tail[0] == '\0')
		return (0);
	i = ft_strlen(tail) - 1;
	j = ft_strlen(str) - 1;
	while (i > 0 && j > 0 && tmp1[j] == tmp2[i])
	{
		i--;
		j--;
	}
	return (tmp1[j] - tmp2[i]);
}
