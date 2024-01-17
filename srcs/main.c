/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:23:07 by fduque-a          #+#    #+#             */
/*   Updated: 2023/12/08 18:57:18 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//global variable exit code
int	g_exit;

// Initializes variables in shell struct
void	shell_init(t_shell *shell, char **envp)
{
	char	*home;

	g_exit = 0;
	shell->nbr_commands = 1;
	shell->prompt = NULL;
	shell->ui = NULL;
	shell->lexer = NULL;
	shell->env_lst = NULL;
	shell->parser = NULL;
	shell->mini_env = copy_envp(envp);
	create_env_list(shell);
	home = get_env_value(shell, "HOME");
	shell->home = ft_strdup(home);
	free(home);
	shell->index = malloc(sizeof(t_index));
	reset_index(shell->index);
	shell->fd_in = STDIN_FILENO;
	shell->fd_out = STDOUT_FILENO;
	shell->pipes = NULL;
	shell->heredoc = 0;
	shell->heredoc_fd = NULL;
	shell->files = NULL;
}

void	set_nulls(t_shell *sh)
{
	sh->ui = NULL;
	sh->lexer = NULL;
	sh->parser = NULL;
	sh->heredoc_fd = NULL;
	sh->prompt = NULL;
	sh->pipes = NULL;
	sh->files = NULL;
	sh->cmds = NULL;
	sh->hd_quotes_eof = 0;
	sh->heredoc = 0;
}

// Frees resourses and calls ft_loop
void	reset_loop(t_shell *shell)
{
	if (shell->ui)
		free(shell->ui);
	if (shell->lexer)
		free_lexer_list(shell->lexer);
	if (shell->parser)
		free_parser_tree(shell->parser);
	if (shell->prompt)
		free(shell->prompt);
	if (shell->pipes)
		free_int_matrix(shell);
	if (shell->files)
		free(shell->files);
	set_nulls(shell);
	reset_index(shell->index);
	shell->nbr_commands = 1;
	shell->fd_in = STDIN_FILENO;
	shell->fd_out = STDOUT_FILENO;
	ft_loop(shell);
}

void	ft_loop(t_shell *shell)
{
	shell->prompt = get_prompt(shell);
	shell->ui = readline(shell->prompt);
	if (!shell->ui)
		empty_line(shell);
	handle_empty_line(shell);
	add_history(shell->ui);
	open_pipe(shell);
	expand_line(shell, shell->ui - 1);
	shell->lexer = ft_lexer(shell->ui, shell);
	if (!shell->lexer)
		reset_loop(shell);
	if (is_syntax_correct(shell->lexer))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		g_exit = is_syntax_correct(shell->lexer);
		reset_loop(shell);
	}
	heredoc_check(shell->lexer, shell);
	shell->parser = build_tree(&(shell->lexer), shell);
	create_pipes(shell);
	executor(shell, shell->parser, 0);
	close_pipes(shell);
	reset_loop(shell);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (argc != 1 || argv[1])
	{
		printf("minishell cannot receive arguments\n");
		exit(0);
	}
	if (envp[0] == NULL)
		return (0);
	shell_init(&shell, envp);
	reset_signals();
	ft_loop(&shell);
}
