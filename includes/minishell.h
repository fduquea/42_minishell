/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:37:26 by fduque-a          #+#    #+#             */
/*   Updated: 2023/12/13 19:46:02 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <stdbool.h>
# include <errno.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/stat.h>

# include "../libft/include/libft.h"
# include "structs.h"
# include "lexer_parser.h"
# include "expander.h"
# include "executor.h"
# include "builtins.h"
# include "heredoc_pipe.h"
# include "clean.h"
# include "print_stuff.h"

# define TRUE 1
# define FALSE 0
# define BUFFER_PATH 10000
# define MINISHELL "minishell:"

//global variable exit code
extern int	g_exit;

// Located at *main.c*
void		reset_loop(t_shell *shell);
void		ft_loop(t_shell *shell);

// Located in *prompt.c*
void		empty_line(t_shell *sh);
void		handle_empty_line(t_shell *sh);
char		*get_prompt(t_shell *shell);

// Located in signals.c
void		sigint_handler(int signo);
void		sighandler_child(int signo);
void		child_signals(void);
void		reset_signals(void);

// Located in signals2.c
void		set_exit_status(int status);
void		heredoc_handler(int signo);

// Located in *env.c*
t_envlst	*ft_lstnew_env(char *key, char *value, int visible);
char		*get_key(char *mini_env);
char		*get_value(char *mini_env);
void		create_env_list(t_shell *shell);

// Located in *env_utils.c*
void		free_env_lst(t_envlst *env_lst);
void		free_node_env(t_envlst *node);
void		free_nodes_env(t_envlst **list);
char		**copy_envp(char **envp);
void		ft_lstadd_back_env(t_envlst **head, t_envlst *new_node);

// Located in *envlst_use.c*
int			ft_list_size_env(t_envlst *list);
void		join_mini_env(t_envlst *env_lst, char **mini_env, int i);
void		update_mini_env(t_shell *shell);
char		*get_env_value(t_shell *shell, char *key);
int			change_env_value(t_shell *shell, char *key, char *new_value);

// Located in *builtin_env.c*
void		print_env_list(t_shell *shell);

#endif
