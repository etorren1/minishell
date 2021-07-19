#include "../includes/minishell.h"

void	up_shlvl(char ***envp)
{
	int		ret;
	int		lvl;
	char	*newlvl;
	char	*tmp;

	ret = find_environment("SHLVL", *envp);
	if (ret >= 0)
	{
		lvl = ft_atoi(&(*envp)[ret][6]);
		lvl++;
		tmp = ft_itoa(lvl);
		newlvl = ft_strdup("SHLVL=");
		newlvl = ft_strjoin(newlvl, tmp);
		(*envp)[ret] = ft_realloc((*envp)[ret], ft_strlen(newlvl) + 1);
		ft_strcpy((*envp)[ret], newlvl);
		free(newlvl);
		free(tmp);
	}
	else
		*envp = ft_arradd_str(*envp, "SHLVL=1", 12);
}
