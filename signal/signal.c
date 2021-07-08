/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masharla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 22:46:23 by masharla          #+#    #+#             */
/*   Updated: 2021/07/06 22:46:24 by masharla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl_c_handler(int sig)
{
	signal(SIGINT, ctrl_c_handler);
	write (1, "\n", 1);
	write (1, MINISHELL, PROMPT);
}

void 	ctrl_backslash_handler(int sig)
{
	;
}

void	print_ouit(int sig)
{
	write(1, "Quit\n", 5);
}
