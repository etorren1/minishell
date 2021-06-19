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

#include "../../includes/minishell.h"

void	ft_exit(t_cmd *cmd)
{
	/*struct	termios term;
	tcgetattr(0, &term);
	term.c_lflag |= (ECHO);
	term.c_lflag |= (ICANON);
	tcsetattr(0, TCSANOW, &term);*/

	printf("exit(doesn't work)\n");
	exit(0);
}
