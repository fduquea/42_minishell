/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:09:14 by fduque-a          #+#    #+#             */
/*   Updated: 2023/12/13 20:02:13 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"
# include "structs.h"
# include "executor.h"

// Located in *expand_utils.c*
int		remove_empty(char **cmds, int nbr_cmds);
int		expand_cmds(char *key, int i, int j, char **line);
void	handle_invalid_env(int point, int len, char **line);
void	expand_valid_env(int start, t_shell *sh, char *env_value, char **line);
int		expand_free(char *key, int i, int j, char **line);

// Located in *expand_arg.c*
int		find_dollar(t_shell *sh, int point, char *tmp, char **line);
int		check_quotes_str(const char *str, t_shell *sh);
void	update_cmds(t_shell *sh, char *value, char **line);
void	env_expand_dollar(t_shell *sh, char *tmp, char **line);

// Located in *expander.c*
void	expand_line(t_shell *sh, char *tmp);
void	expander(char ***cmds, t_shell *sh);
char	*trim_whitespace(t_shell *sh, char *str);

#endif