/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:05:50 by arepsa            #+#    #+#             */
/*   Updated: 2023/12/26 12:33:55 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipeline_child(t_shell *sh)
{
	int		fd;
	char	*line;

	fd = open(".pipe", O_RDWR | O_CREAT, 0644);
	line = readline("> ");
	if (!line && g_exit != 130)
		handle_empty_line_exit(sh, fd);
	while (g_exit != 130 && is_empty_line(line))
	{
		free(line);
		line = readline("> ");
		if (!line && g_exit != 130)
			handle_empty_line_exit(sh, fd);
	}
	if (g_exit != 130)
		ft_putstr_fd(line, fd);
	free(line);
	close(fd);
	close(0);
	unlink(".nfs00000013f1dca27b");
	clear_shell(sh);
	if (g_exit == 130)
		exit(2);
	exit(0);
}

int	pipeline_parent(t_shell *sh, pid_t pid)
{
	int		fd;
	int		status;
	char	*tempstr;

	tempstr = NULL;
	waitpid(pid, &status, 0);
	reset_signals();
	if (WEXITSTATUS(status) == 2)
	{
		write(1, "\n", 1);
		g_exit = 130;
		unlink(".pipe");
		reset_loop(sh);
	}
	fd = open(".pipe", O_RDWR);
	tempstr = get_next_line(fd);
	close(fd);
	unlink(".pipe");
	handle_just_pipe(sh, tempstr);
	if (WEXITSTATUS(status) != 3)
		sh->ui = ft_strjoin_gnl(sh->ui, tempstr);
	free(tempstr);
	return (status);
}

char	*open_pipe(t_shell *sh)
{
	char	*temp;
	pid_t	pid;

	temp = ft_strtrim(sh->ui, WHITESPACE);
	while (temp[ft_strlen(temp) - 1] == '|')
	{
		free(temp);
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid == 0)
		{
			g_exit = 0;
			signal(SIGINT, heredoc_handler);
			reset_index(sh->index);
			pipeline_child(sh);
		}
		else if (pipeline_parent(sh, pid) == 768)
		{
			clear_shell(sh);
			exit(2);
		}
		temp = ft_strtrim(sh->ui, WHITESPACE);
	}
	free(temp);
	return (sh->ui);
}
