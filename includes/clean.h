/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:58:17 by fduque-a          #+#    #+#             */
/*   Updated: 2023/12/08 17:22:25 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAN_H
# define CLEAN_H

# include "minishell.h"
# include "structs.h"

// Located in *clean_shell.c*
void	clear_shell(t_shell *shell);
void	mini_clean(t_shell *sh, int i);

// Located in clean_lexer.c
void	lexer_delone(t_lexer **lexer, int key);
void	lexer_free_node(t_lexer *node);
void	free_lexer_list(t_lexer *head);
void	free_lexer_list_rev(t_lexer **tail);

// Located in *clean.c*
void	reset_index(t_index *index);
void	free_matrix(char **matrix);
void	free_int_matrix(t_shell *shell);
void	delete_heredoc_list(t_shell *sh);
void	free_parser_tree(t_tree_node *root);

// Located in *error_msg.c*
int		error_3s(char *str1, char *str2, char *str3);
int		error_4s(char *str1, char *str2, char *str3, char *str4);
int		short_error(char *str1, char *str2, char *str3, int exit_no);

// Located in *error.c*
bool	empty_redir(t_lexer *lexer);
bool	double_operator(t_lexer *lexer);
int		is_syntax_correct(t_lexer *lexer);

#endif
