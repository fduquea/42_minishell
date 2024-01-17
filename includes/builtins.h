/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:05:18 by arepsa            #+#    #+#             */
/*   Updated: 2023/12/08 18:34:45 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "structs.h"

// Located in *b_cd.c*
bool	is_home(t_shell *shell, char **cmds);
int		builtin_cd(t_shell *shell, char **cmds);

// Located in *b_echo.c*
int		builtin_echo(char **cmds);

// Located in *b_env.c*
int		builtin_env(t_shell *shell, char **cmds);

// Located in *b_exit.c*
void	builtin_exit(t_shell *shell, char **cmds);

// Located in *b_export.c*
int		builtin_export(t_shell *shell, char **cmds);
// Located in *b_export_utils.c*
void	print_export(t_shell *shell);

// Located in *b_pwd.c*
int		builtin_pwd(void);

// Located in *b_unset.c*
int		builtin_unset(t_shell *shell, char **cmds);

// Located in *b_main.c*
bool	strn_strl_cmp(char *s1, char *s2);
bool	is_builtin_parent(char **cmd);
bool	is_builtin_child(char **cmd);
int		builtin_router(t_shell *shell, char **cmds);

#endif