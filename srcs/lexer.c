/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:53:39 by damachad          #+#    #+#             */
/*   Updated: 2023/09/20 15:55:30 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Checks if char is one of those in the str

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

// Checks for operators and returns flag

int	is_operator(char *word)
{
	if (word[0] == '|' && !is_present("|<>", word[1]))
		return (PIPE);
	else if (word[0] == '>' && word[1] == '>' && !is_present("|<>", word[2]))
		return (DOU_GREAT);
	else if (word[0] == '<' && word[1] == '<' && !is_present("|<>", word[2]))
		return (DOU_LESS);
	else if (word[0] == '<' && !is_present("|<>", word[1]))
		return (LESS);
	else if (word[0] == '>' && !is_present("|<>", word[1]))
		return (GREAT);
	else
		return (0);
}

// Advance the index j to the next quote 
// (" or ', depending on the first quote encountered)

void	advance_quote(char *str, int *j, char next_char)
{
	(*j)++;
	while (str[*j] && str[*j] != next_char)
		(*j)++;
	if (str[*j] == next_char)
		(*j)++;
}

// Advance the index j to the next space

void	advance_word(char *str, int *j)
{
	while (str[*j] && str[*j] != ' ')
		(*j)++;
}

// Create a new node of type t_lexer and initialize it 
// with the word passed as parameter, the index of the node 
// and the operator (which one)

t_lexer	*lexer_new(char *word, int i)
{
	t_lexer		*new;
	new = malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->str = word;
	new->token = is_operator(word);
	new->i = i;
	new->next = NULL;
	return (new);
}

// Add a new node of type t_lexer at the end of the list

void	lexer_add_back(t_shell **shell, t_lexer *new)
{
	t_lexer	*tmp;

	if (!(*shell)->lexer)
		(*shell)->lexer = new;
	tmp = (*shell)->lexer;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp != new)
		tmp->next = new;
}

// Create a linked list of type t_lexer from the command_buffer,
// caller function

void ft_lexer(t_shell **shell, char *command_buffer)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (command_buffer[i])
	{
		if (command_buffer[i] == ' ')
			i++;
		else
		{
			j = i;
			if (command_buffer[j] == '\"' || command_buffer[j] == '\'')
				advance_quote(command_buffer, &j, command_buffer[j]);
			else
				advance_word(command_buffer, &j);
			lexer_add_back(shell, lexer_new(ft_substr(command_buffer, i, j - i), k));
			k++;
			i = j;
		}
	}
}
