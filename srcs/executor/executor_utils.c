/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:56:29 by fduque-a          #+#    #+#             */
/*   Updated: 2023/12/12 14:11:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_command_not_found(t_shell *shell, const char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((char *)command, 2);
	ft_putstr_fd(": command not found\n", 2);
	mini_clean(shell, 3);
}

void	handle_file_not_found(t_shell *shell, const char *file)
{
	ft_putstr_fd("minishell: ", 2);
	perror(file);
	mini_clean(shell, 4);
}

void	handle_command_doesnt_exist(t_shell *shell, const char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((char *)command, 2);
	if (errno == EACCES)
	{
		ft_putstr_fd(": Permission denied\n", 2);
		mini_clean(shell, 126);
	}
	else if (errno == ENOENT)
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		mini_clean(shell, 127);
	}
	else if (is_directory(command))
	{
		ft_putstr_fd(": is a directory\n", 2);
		mini_clean(shell, 126);
	}
	else
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	mini_clean(shell, errno);
}

// Creates all necessary pipes for the execution of the commands
// and keeps them in the t_shell struct (**pipes)
void	create_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->nbr_commands > 1)
	{
		shell->pipes = ft_calloc(shell->nbr_commands, sizeof(int *));
		while (i < shell->nbr_commands)
		{
			shell->pipes[i] = malloc(sizeof(int) * 2); 
			if (pipe(shell->pipes[i]) == -1)
				exit(error_3s("pipe creation", "", ""));
			i++;
		}
	}
}

// Closes all pipes created for the execution of the commands
// and the file descriptor 3 (used for the make leaks' "output.log")
void	close_pipes(t_shell *sh)
{
	int	i;

	i = -1;
	if (sh->nbr_commands > 1)
	{
		while (++i <= sh->nbr_commands - 1)
		{
			close(sh->pipes[i][0]);
			close(sh->pipes[i][1]);
		}
	}
}
