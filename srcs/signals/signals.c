/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:39:06 by fduque-a          #+#    #+#             */
/*   Updated: 2023/12/08 11:00:09 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	This function writes the prompt in the terminal
*/
void	redisplay_prompt(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*
**	This function sets program response to CTRL+C
*/
void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_exit = 130;
		redisplay_prompt();
	}
}

/*
**	child sighandler sets exit status, does not reset prompt
*/
void	sighandler_child(int signo)
{
	if (signo == SIGINT || signo == SIGQUIT)
		g_exit = 128 + signo;
}

/*
**	This function sets the signals to their child behavior
*/
void	child_signals(void)
{
	signal(SIGINT, sighandler_child);
	signal(SIGQUIT, sighandler_child);
}

/*
**	This function resets the signals to their default behavior
* SIGINT - CTRL + C
* SIGQUIT - CTRL + \
*/
void	reset_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
