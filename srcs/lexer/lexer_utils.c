/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:50:22 by fduque-a          #+#    #+#             */
/*   Updated: 2023/12/18 18:29:36 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	Checks if a char is part of the string
*/
bool	is_present(const char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (true);
	}
	return (false);
}

/*
**	Searches for < > << >> | and returns the flag
*/
int	is_operator(char *word, t_shell *sh)
{
	if (word[0] == '|' && !is_present(OPERATORS, word[1]))
	{
		sh->nbr_commands++;
		return (PIPE);
	}
	else if (word[0] == '>' && word[1] == '>' && \
	!is_present(OPERATORS, word[2]))
		return (DOU_GREAT);
	else if (word[0] == '<' && word[1] == '<' && \
	!is_present(OPERATORS, word[2]))
	{
		sh->heredoc++;
		return (DOU_LESS);
	}
	else if (word[0] == '<' && !is_present(OPERATORS, word[1]))
		return (LESS);
	else if (word[0] == '>' && !is_present(OPERATORS, word[1]))
		return (GREAT);
	else
		return (WORD);
}

/*
**	Advances the index j to the next quote so I closes
*/
void	advance_quote(char *str, int *j, char next_char)
{
	(*j)++;
	while (str[*j] && str[*j] != next_char)
		(*j)++;
	if (str[*j] == next_char)
		(*j)++;
}

/*
**	Advances the index j to the next space,
** and separates operators from words
*/
void	advance_word(char *str, int *j)
{
	bool	quotes;

	if (str[*j] && is_present(OPERATORS, str[*j]))
	{
		while (str[*j] && is_present(OPERATORS, str[*j]))
			(*j)++;
		return ;
	}
	while (str[*j] && !is_present(WHITESPACE, str[*j]) && \
	!is_present(OPERATORS, str[*j]))
	{
		if (is_present("\"\'", str[*j]))
		{
			quotes = !quotes;
			advance_quote(str, j, str[*j]);
		}
		else
			(*j)++;
	}
}

/*
** Calculates the end position of a token or quoted section
** and advances the index i
*/
void	find_token_end(char *ui, t_shell *shell)
{
	shell->index->j = shell->index->i;
	if (ui[shell->index->j] == '\"' || ui[shell->index->j] == '\'')
	{
		advance_quote(ui, &shell->index->j, ui[shell->index->j]);
		while (ui[shell->index->j] != 32 && ui[shell->index->j] != '\0')
		{
			if (ui[shell->index->j] == '\"' || ui[shell->index->j] == '\'')
				advance_quote(ui, &shell->index->j, ui[shell->index->j]);
			else
				advance_word(ui, &shell->index->j);
		}
	}
	else
		advance_word(ui, &shell->index->j);
}
