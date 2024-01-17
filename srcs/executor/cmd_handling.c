/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:45:12 by fduque-a          #+#    #+#             */
/*   Updated: 2023/12/18 17:24:18 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//aux function for exec_cmds
void	handle_null_path(t_shell *sh, char **cmds)
{
	if (ft_strchr(cmds[0], '/') != NULL)
		handle_command_doesnt_exist(sh, cmds[0]);
	else if (cmds[0][0] == '=')
		handle_command_not_found(sh, cmds[0]);
	else if (ft_strchr(cmds[0] + 1, '=') != NULL)
		mini_clean(sh, 0);
	else
		handle_command_not_found(sh, cmds[0]);
}

// Initialize cmd_blocks, get path, test it and execute
void	exec_cmds(t_shell *sh, char **cmds)
{
	char	*path;

	path = NULL;
	if (is_absolute_path(cmds[0]))
	{
		path = ft_strdup(cmds[0]);
		if (is_directory(cmds[0]))
		{
			handle_command_doesnt_exist(sh, cmds[0]);
			return ;
		}
	}
	else if (cmds[0][0])
		path = find_path(cmds[0], sh);
	if (path == NULL)
	{
		handle_null_path(sh, cmds);
	}
	execve(path, cmds, sh->mini_env);
	ft_putstr_fd("minishell: execve", 2);
	mini_clean(sh, 1);
}

void	no_access_output(t_shell *sh, char *str)
{
	g_exit = 1;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	mini_clean(sh, 1);
}

void	handle_output_redir(t_shell *sh, t_tree_node *node)
{
	t_lexer	*temp;

	temp = node->out_redirs;
	while (node->out_redirs)
	{
		remove_quotes_heredoc(node->out_redirs->str);
		if (!access(node->out_redirs->str, F_OK) && \
			access(node->out_redirs->str, W_OK))
		{
			no_access_output(sh, node->out_redirs->str);
		}
		if (node->out_redirs->operator == DOU_GREAT)
			sh->fd_out = open(node->out_redirs->str, O_WRONLY \
			| O_CREAT | O_APPEND, 0644);
		else
			sh->fd_out = open(node->out_redirs->str, O_WRONLY \
			| O_CREAT | O_TRUNC, 0644);
		if (node->cmd && check_cmds(sh, node->cmd))
			dup2(sh->fd_out, STDOUT_FILENO);
		node->out_redirs = node->out_redirs->next;
		close(sh->fd_out);
	}
	node->out_redirs = temp;
}

void	handle_input_redir(t_shell *sh, t_tree_node *node)
{
	t_lexer	*temp;

	temp = node->in_redirs;
	while (node->in_redirs)
	{
		remove_quotes_heredoc(node->in_redirs->str);
		if (access(node->in_redirs->str, R_OK))
			handle_file_not_found(sh, node->in_redirs->str);
		sh->fd_in = open(node->in_redirs->str, O_RDONLY);
		if (node->cmd && check_cmds(sh, node->cmd))
			dup2(sh->fd_in, STDIN_FILENO);
		node->in_redirs = node->in_redirs->next;
		close(sh->fd_in);
	}
	node->in_redirs = temp;
}
