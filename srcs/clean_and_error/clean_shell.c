/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:56:40 by fduque-a          #+#    #+#             */
/*   Updated: 2023/12/13 19:47:14 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	This function frees the memory allocated
*/
void	free_shell_fields(t_shell *shell)
{
	if (shell->ui)
		free(shell->ui);
	if (shell->lexer)
		free_lexer_list(shell->lexer);
	if (shell->parser)
		free_parser_tree(shell->parser);
	if (shell->env_lst)
		free_env_lst(shell->env_lst);
	if (shell->mini_env)
		free_matrix(shell->mini_env);
	if (shell->index)
		free(shell->index);
	if (shell->home)
		free(shell->home);
	if (shell->prompt)
		free(shell->prompt);
	if (shell->pipes)
		free_int_matrix(shell);
	if (shell->files)
		free(shell->files);
}

/*
**	This function frees the memory allocated
*/
void	clear_shell(t_shell *shell)
{
	free_shell_fields(shell);
	shell->ui = NULL;
	shell->lexer = NULL;
	shell->parser = NULL;
	shell->env_lst = NULL;
	shell->mini_env = NULL;
	shell->index = NULL;
	shell->home = NULL;
	shell->prompt = NULL;
	shell->pipes = NULL;
	shell->files = NULL;
}

/*
**	Call this function at the end 
** of each handle_not_found() call
*/
void	mini_clean(t_shell *sh, int i)
{
	close(sh->fd_in);
	close(sh->fd_out);
	close(0);
	close(1);
	close_pipes(sh);
	clear_shell(sh);
	exit(i);
}
