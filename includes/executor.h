/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:53:37 by fduque-a          #+#    #+#             */
/*   Updated: 2023/12/18 17:23:33 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include "structs.h"

# define READ_END 0
# define WRITE_END 1
# define WHITESPACE "\t\n\v\f\r "
# define NOT_EXPRESSION "|><&();/ \t\n\v\f\r"

// Located at *cmd_handling.c*
void	exec_cmds(t_shell *sh, char **cmds);
void	handle_output_redir(t_shell *sh, t_tree_node *node);
void	handle_input_redir(t_shell *sh, t_tree_node *node);

// Located at *cmd_utils.c*
char	*ft_strtok(char *str, char *delimiter);
bool	is_directory(const char *path);

// Located at *executor_utils.c*
void	handle_command_not_found(t_shell *shell, const char *command);
void	handle_file_not_found(t_shell *shell, const char *file);
void	handle_command_doesnt_exist(t_shell *shell, const char *command);
void	create_pipes(t_shell *shell);
void	close_pipes(t_shell *sh);

// Located at *path.c*
bool	check_cmds(t_shell *sh, char **cmds);
int		is_absolute_path(char *cmd);
char	*search_executable(char *cmd, char *path_env);
char	*find_path(char *cmd, t_shell *shell);

// Located at *executor.c*
void	executor(t_shell *sh, t_tree_node *parser, int i);

#endif
