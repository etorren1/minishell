#include "../includes/readterm.h"

static void	replace_ruschar(t_rl *rl, int count)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = malloc(ft_strlen(rl->command_line) + count + 1);
	while (rl->command_line[i])
	{
		if (rl->command_line[i] < -112)
			tmp[j++] = -47;
		else if (rl->command_line[i] < -64)
			tmp[j++] = -48;
		tmp[j++] = rl->command_line[i++];
	}
	tmp[j] = 0;
	ft_strcpy(rl->command_line, tmp);
	free(tmp);
}

void	add_rus(t_rl *rl)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (rl->command_line[++i])
		if (rl->command_line[i] < 0)
			count++;
	if (count > 0)
	{
		if (rl->len <= (int)ft_strlen(rl->command_line) + count)
		{
			rl->len += count;
			rl->command_line = ft_realloc(rl->command_line, rl->len);
		}
		replace_ruschar(rl, count);
	}
}
