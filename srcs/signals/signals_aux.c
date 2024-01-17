/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:49:22 by fduque-a          #+#    #+#             */
/*   Updated: 2023/12/13 20:14:27 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_exit_status(int status)
{
	if (WTERMSIG(status))
		g_exit = 128 + WTERMSIG(status);
	else if (WEXITSTATUS(status) == 1 || WEXITSTATUS(status) == 4)
		g_exit = 1;
	else if (WEXITSTATUS(status) == 3)
		g_exit = 127;
	else if (WEXITSTATUS(status) == 13 || WEXITSTATUS(status) == 20 \
			|| WEXITSTATUS(status) == 21)
		g_exit = 126;
	else
		g_exit = WEXITSTATUS(status);
	if (g_exit == 130)
		write(1, "\n", 1);
	else if (g_exit == 131)
		write(2, "Quit: (core dumped)\n", 20);
}

void	heredoc_handler(int signo)
{
	int	fd;

	fd = 0;
	if (signo == SIGINT)
	{
		g_exit = 130;
		fd = open(".nfs00000013f1dca27b", O_WRONLY | O_TRUNC | O_CREAT, 0644);
		dup2(fd, 0);
		close(fd);
		ioctl(0, TIOCSTI, "\n");
	}
}
