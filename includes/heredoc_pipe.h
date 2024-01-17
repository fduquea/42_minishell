/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pipe.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:17:13 by fduque-a          #+#    #+#             */
/*   Updated: 2023/12/18 17:39:07 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_PIPE_H
# define HEREDOC_PIPE_H

# include "minishell.h"
# include "structs.h"

# define HERE_MSG "warning: here-document delimited by end-of-file (wanted"

// Located in *heredoc_utils.c*
void	heredoc_maker(t_lexer *heredoc_node, t_shell *sh);

// Located in *heredoc.c*
void	remove_quotes_heredoc(char *str);
void	heredoc_check(t_lexer *lexer, t_shell *sh);

// Located in *open_pipes.c
char	*open_pipe(t_shell *sh);

// Located in *pipe_utils.c
bool	is_empty_line(char *str);
void	handle_empty_line_exit(t_shell *sh, int fd);
void	handle_just_pipe(t_shell *sh, char *str);

#endif