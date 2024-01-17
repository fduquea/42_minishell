/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:21:02 by fduque-a          #+#    #+#             */
/*   Updated: 2023/12/13 19:41:13 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PARSER_H
# define LEXER_PARSER_H

# include "minishell.h"
# include "structs.h"

// Macros
# define OPERATORS "<>|"
# define CMD 2

// Located in *lexer.c*
t_lexer		*last_node(t_lexer *start);
t_lexer		*lexer_new(char *word, int i, t_shell *sh);
void		lexer_add_back(t_lexer **lexer, t_lexer *new);
t_lexer		*ft_lexer(char *ui, t_shell *sh);

// Located in *lexer_utils.c*
bool		is_present(const char *str, char c);
int			is_operator(char *word, t_shell *sh);
void		advance_quote(char *str, int *j, char next_char);
void		advance_word(char *str, int *j);
void		find_token_end(char *ui, t_shell *shell);

// Located in *parser_utils.c*
t_tree_node	*command_node(t_lexer **start, t_lexer *end, t_shell *shell);

// Located in *parser.c*
void		list_to_array(t_lexer *start, t_lexer *end, char ***cmd);
t_tree_node	*build_tree(t_lexer **start, t_shell *shell);

#endif
