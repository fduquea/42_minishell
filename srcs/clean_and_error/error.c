/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:20:27 by fduque-a          #+#    #+#             */
/*   Updated: 2023/12/08 17:21:49 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	This function checks if there is a double operator
*/
bool	double_operator(t_lexer *lexer)
{
	t_lexer	*curr;
	t_lexer	*prev;

	curr = lexer;
	while (curr)
	{
		prev = curr;
		curr = curr->next;
		if (curr && prev->operator && curr->operator)
		{
			if (prev->operator == PIPE && curr->operator != PIPE)
				continue ;
			else
				return (true);
		}
	}
	return (false);
}

/*
**	This function checks if the syntax is correct
*/
int	is_syntax_correct(t_lexer *lexer)
{
	t_lexer	*tmp;

	tmp = lexer;
	if (tmp && tmp->str[0] == '|')
		return (2);
	while (tmp)
	{
		if (tmp->str[0] == '|' && is_present(OPERATORS, tmp->str[1]))
			return (2);
		if (tmp->str[0] == '<' && is_present("|>", tmp->str[1]))
			return (2);
		if (tmp->str[0] == '>' && is_present("|<", tmp->str[1]))
			return (2);
		if (tmp->str[0] == '>' && tmp->str[1] == '>' \
		&& is_present(OPERATORS, tmp->str[2]))
			return (2);
		if (tmp->str[0] == '<' && tmp->str[1] == '<' \
		&& is_present(OPERATORS, tmp->str[2]))
			return (2);
		tmp = tmp->next;
	}
	if (double_operator(lexer) || empty_redir(lexer))
		return (2);
	return (0);
}

/*
**	This function is called when 
** there is no redirection found
*/
bool	empty_redir(t_lexer *lexer)
{
	t_lexer	*curr;
	t_lexer	*prev;

	curr = lexer;
	while (curr)
	{
		prev = curr;
		curr = curr->next;
		if (!curr && prev->operator)
			return (true);
	}
	return (false);
}
