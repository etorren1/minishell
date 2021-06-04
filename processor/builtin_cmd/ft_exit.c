/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 21:18:19 by etorren           #+#    #+#             */
/*   Updated: 2021/05/23 21:18:20 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <termios.h>
#include "../../includes/minishell.h"

void	ft_exit(void)
{
	struct	termios term;
	tcgetattr(0, &term);
	term.c_lflag |= (ECHO);
	term.c_lflag |= (ICANON);
	tcsetattr(0, TCSANOW, &term);

	tgetent(0, "xterm-256color");
	printf("exit(doesn't work)\n");
	exit(0);
}
