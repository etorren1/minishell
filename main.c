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

int	main(int argc, char **argv, char **envp)
{
	struct	termios term;
	struct	termios saveterm;
	t_rl	*rl;

	if (argc > 1)
		return (0);
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
		//printf("\e[35mCommLine=\"%s\"\e[0m\n", rl->command_line);
		if (ft_strcmp(rl->buf, "\4") && ft_strcmp(rl->buf, "\3"))
			core(rl); 
	}
	clear_exit(rl);
	return (0);
}
