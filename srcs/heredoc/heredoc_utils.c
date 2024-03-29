/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:37:55 by fduque-a          #+#    #+#             */
/*   Updated: 2023/12/08 18:25:36 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** The function that expands the dollar sign in the heredoc
*/
void	env_expand_dollar_hd(t_shell *shell, char *tmp, char **line)
{
	int		dquote;
	int		squote;

	dquote = 0;
	squote = 0;
	while (*(++tmp))
	{
		if (*tmp == '"' && !squote)
			dquote = !dquote;
		if (*tmp == '\'' && !dquote)
			squote = !squote;
		if (*tmp == '$' && !ft_strchr(NOT_EXPRESSION, *(tmp + 1)) && \
		!((dquote || squote) && (*(tmp + 1) == '"' || *(tmp + 1) == '\'')))
		{
			if (find_dollar(shell, tmp - *line, tmp, line))
			{
				tmp = *line - 1;
				dquote = 0;
				squote = 0;
			}
		}
	}
}

/*
**	The function that processes the input from heredoc
*/
void	process_line(t_shell *sh, char **line)
{
	sh->index->i = -1;
	if (sh->hd_quotes_eof != 1)
	{
		while ((*line)[++sh->index->i])
		{
			if ((*line)[sh->index->i] == '$')
			{
				env_expand_dollar_hd(sh, *line - 1, line);
				break ;
			}
		}
	}
	ft_putendl_fd(*line, sh->index->j);
	free(*line);
}

/*
**	Stores input from heredoc in a file
** Ctrl+C returns exit code 130
*/
void	ft_heredoc(t_lexer *heredoc, t_shell *sh)
{
	char	*line;

	line = NULL;
	sh->index->j = open(sh->files, O_RDWR | O_CREAT | O_TRUNC, 0644);
	signal(SIGINT, heredoc_handler);
	while (g_exit != 130)
	{
		line = readline("> ");
		if (g_exit == 130)
			break ;
		if (!line && g_exit != 130)
		{
			printf("%s `%s')\n", HERE_MSG, heredoc->eof);
			break ;
		}
		if (ft_strcmp(line, heredoc->eof) == 0)
		{
			free(line);
			break ;
		}
		process_line(sh, &line);
	}
	close(sh->index->j);
}

/*
**	The child process that executes ft_heredoc()
*/
void	heredoc_child(t_lexer *heredoc_node, t_shell *sh)
{
	g_exit = 0;
	ft_heredoc(heredoc_node, sh);
	close(0);
	unlink(".nfs00000013f1dca27b");
	free_lexer_list_rev(&heredoc_node);
	clear_shell(sh);
	if (g_exit == 130)
		exit(2);
	exit(0);
}

/*
**	Creates the child to execute the ft_heredoc() function
*/
void	heredoc_maker(t_lexer *heredoc_node, t_shell *sh)
{
	pid_t		pid;
	int			status;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		heredoc_child(heredoc_node, sh);
	else
	{
		waitpid(pid, &status, 0);
		reset_signals();
		if (status > 128)
		{
			write(1, "\n", 1);
			g_exit = 130;
			free_lexer_list(sh->heredoc_fd);
			sh->heredoc_fd = NULL;
			delete_heredoc_list(sh);
			reset_loop(sh);
		}
	}
}
