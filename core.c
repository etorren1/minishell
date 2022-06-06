#include "./includes/readterm.h"

int	parse_err(t_rl *rl, int err);

int	count_sumlen(t_cmd **cmd)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (cmd[++i])
		count += cmd[i]->len;
	return (count);
}

int	init_pipe(t_pip *pip, int j, int k)
{
	if (j < k - 1)
	{
		if (pipe(pip->fds[j]))
		{
			ft_putendl_fd("Broken pipe", 2);
			return (1);
		}
	}
	pip->pid[j] = fork();
	if (pip->pid[j] < 0)
	{
		ft_putendl_fd("pid_error", 2);
		return (1);
	}
	return (0);
}

void	pipe_core(t_cmd **cmd, t_pip *pip, t_rl *rl, int k)
{
	while (++pip->j < k)
	{
		rl->status = init_pipe(pip, pip->j, k);
		if (rl->status)
			break ;
		if (pip->pid[pip->j] == 0)
		{
			if (pip->j < k - 1 && cmd[pip->j]->fd_to == 1)
				cmd[pip->j]->fd_to = pip->fds[pip->j][1];
			if (pip->j != 0)
				cmd[pip->j]->fd_from = pip->fds[pip->j - 1][0];
			processor(cmd[pip->j], &rl->env, rl);
			exit(0);
		}
		else
		{
			if (pip->j != 0)
				close(pip->fds[pip->j - 1][0]);
			if (pip->j != k - 1)
				close(pip->fds[pip->j][1]);
			if (cmd[pip->j]->fd_to > 1 && cmd[pip->j]->fd_to
				 != pip->fds[pip->j][1])
				close(cmd[pip->j]->fd_to);
		}						
	}
}

void	pipes(t_rl *rl, t_cmd **cmd, int k)
{
	t_pip	*pip;

	pip = malloc(sizeof(t_pip));
	pip->fds = (int **)malloc(sizeof (int *) * k);
	pip->pid = malloc(sizeof(int) * k);
	pip->j = -1;
	while (++pip->j < k)
		pip->fds[pip->j] = (int *)malloc(sizeof(int) * 2);
	pip->j = -1;
	pipe_core(cmd, pip, rl, k);
	pip->j = -1;
	while (++pip->j < k)
	{
		waitpid(pip->pid[pip->j], &rl->status, 0);
		kill(pip->pid[pip->j], SIGKILL);
		free(pip->fds[pip->j]);
	}
	if (rl->status > 255)
		rl->status /= 256;
	free(pip->fds);
	free(pip->pid);
	free(pip);
}

void	core(t_rl *rl, int k)
{
	t_cmd	**cmd;
	int		i;

	i = 0;
	cmd = NULL;
	while (rl->command_line[i])
	{
		cmd = (t_cmd **)malloc(sizeof(t_cmd));
		*cmd = NULL;
		if (parse_err(rl, parser(&rl->command_line[i], rl, &cmd))) {
			free_arrcmd(cmd);
			break ;
		}
		i += count_sumlen(cmd);
		if (rl->command_line[i])
			i++;
		while (cmd[k])
			k++;
		if (k == 1)
			processor(*cmd, &rl->env, rl);
		else if (k > 1)
			pipes(rl, cmd, k);
		free_arrcmd(cmd);
	}
	if (rl->mode)
		free(rl->mode);
}
