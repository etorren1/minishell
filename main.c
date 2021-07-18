/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masharla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 11:21:53 by etorren           #+#    #+#             */
/*   Updated: 2021/07/11 14:48:45 by masharla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/readterm.h"

int count_sumlen(t_cmd **cmd)
{
	int count;
	int i;

	count = 0;
	i = -1;
	while (cmd[++i])
		count += cmd[i]->len;
	return count;
}

void	clear_exit(t_rl *rl)
{
	close(rl->fd);
	rl->fd = open(rl->history, O_WRONLY | O_TRUNC, 0777);
	rl->histnode = ft_nodefirst(rl->histnode);
	while (rl->histnode->next)
	{
		write(rl->fd, rl->histnode->content, ft_strlen(rl->histnode->content));
		write(rl->fd, "\n", 1);
		rl->histnode = rl->histnode->next;
	}
	write (1, "exit\n", 5);
	free(rl->history);
	free(rl->command_line);
	close (rl->fd);
	free(rl);
	ft_arrfree(rl->env);
}

int		omg(t_rl *rl)
{
	t_cmd **cmd;

	if (ft_strcmp(rl->buf, "\4") && ft_strcmp(rl->buf, "\3"))
	{
		int i = 0;
		cmd = NULL;
		while (rl->command_line[i]) 
		{
			if (cmd)
				free_arrcmd(cmd);
			cmd = (t_cmd **)malloc(sizeof(cmd));
			*cmd = NULL;
			int err;
			err = parser(&rl->command_line[i], rl, &cmd);
			if (err < 0)
			{
				rl->status = 1;
				if (err == -1)
					ft_putendl_fd("minishell: syntax error near unexpected token", 2);
				else if (err == -2)
					rl->status = 2;
				else
					ft_putendl_fd("minishell: parser error", 2);
				break ;
			}
			i += count_sumlen(cmd);
			if (rl->command_line[i])
				i++;
			// считаем элементы
			int k = 0;
			
			while (cmd[k])
				k++;
			// если без пайпов
			if (k == 1)
				processor(*cmd, &rl->env, rl);
			// если пайпы
			else if (k > 1)
			{
				int **fds = (int **)malloc(sizeof (int *) * (k - 1));
				int j = -1;
				int *pid;
				int status;

				pid = malloc(sizeof(int) * k);
				while (++j < k)
					fds[j] = (int *)malloc(sizeof(int) * 2);
				j = -1;
				while (++j < k)
				{
					if (j < k - 1)
					{
						if (pipe(fds[j]))
						{
							ft_putendl_fd("Broken pipe", 2);
							rl->status = 1;
							break ;
						}
					}
					pid[j] = fork();
					if (pid[j] < 0)
					{
						ft_putendl_fd("pid_error", 2);
						rl->status = 1;
						break ;
					}
					else if (pid[j] == 0)
					{
						if (j < k - 1 && cmd[j]->fd_to == 1)
							cmd[j]->fd_to = fds[j][1];
						if (j != 0)
							cmd[j]->fd_from = fds[j - 1][0];
						processor(cmd[j], &rl->env, rl);
						exit(0);
					}
					else
					{
						if (j != 0)
							close(fds[j - 1][0]);
						if (j != k - 1)
							close(fds[j][1]);
						if (cmd[j]->fd_to > 1 && cmd[j]->fd_to != fds[j][1])
							close(cmd[j]->fd_to);
					}						
				}
				j = -1;
				while (++j < k)
				{
					waitpid(pid[j], &rl->status, 0);
					kill(pid[j], SIGKILL);
					free(fds[j]);
				}
				if (rl->status > 255)
					rl->status /= 256;				
				free(fds);
				free(pid);
			}
		}
		if (cmd)
			free_arrcmd(cmd);
		if (rl->mode)
			free(rl->mode);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	struct	termios term;
	struct	termios saveterm;
	t_rl	*rl;
	char	**env;

	tgetent(0, "xterm-256color");
	tcgetattr(0, &saveterm);
	tcgetattr(0, &term);
	rl = init_rl(argv[0], envp);
	up_shlvl(&rl->env);
	while (ft_strcmp(rl->buf, "\4") || rl->command_line[0] != 0)
	{
		preread(rl, &term);
		readterm(rl, &rl->histnode);
		tcsetattr(0, TCSANOW, &saveterm);
		printf("\e[35mCommLine=\"%s\"\e[0m\n", rl->command_line);
		omg(rl); // parser and processor part
	}
	clear_exit(rl);
	return (0);
}
