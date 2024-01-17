/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:14:54 by arepsa            #+#    #+#             */
/*   Updated: 2023/12/13 19:49:16 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	Lexer_delone aux
*/
void	delete_node(t_lexer **lexer, t_lexer *curr, t_lexer *prev)
{
	t_lexer	*tmp;

	if (prev)
		prev->next = curr->next->next;
	else
	{
		if (!curr->prev)
		{
			*lexer = curr->next->next;
			if (*lexer)
				(*lexer)->prev = NULL;
		}
		else
		{
			prev = curr->prev;
			prev->next = curr->next->next;
			*lexer = curr->next->next;
		}
	}
	tmp = curr->next;
	lexer_free_node(curr);
	lexer_free_node(tmp);
}

/*
**	Deletes a node of the lexer linked listD
*/
void	lexer_delone(t_lexer **lexer, int key)
{
	t_lexer	*curr;
	t_lexer	*prev;

	curr = *lexer;
	prev = NULL;
	if (!(*lexer))
		return ;
	while (curr && curr->next)
	{
		if (curr->i == key)
		{
			delete_node(lexer, curr, prev);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

/*
**	This function frees the memory allocated
** for a node of the lexer linked list
*/
void	lexer_free_node(t_lexer *node)
{
	if (node)
	{
		if (node->str)
			free(node->str);
		node->prev = NULL;
		free(node);
	}
}

/*
**	Frees the allocated memory
*/
void	free_lexer_list(t_lexer *head)
{
	t_lexer	*current; 
	t_lexer	*next;

	current = head;
	next = NULL;
	if (!head)
		return ;
	while (current)
	{
		next = current->next;
		if (current->str)
		{
			free(current->str);
			current->str = NULL;
		}
		free(current);
		current = next;
	}
}

/*
**	This function frees the lexer list in reverse
*/
void	free_lexer_list_rev(t_lexer **tail)
{
	t_lexer	*current; 
	t_lexer	*prev;

	current = *tail;
	prev = NULL;
	if (!tail)
		return ;
	while (current)
	{
		prev = current->prev;
		if (current->str)
		{
			free(current->str);
			current->str = NULL;
		}
		free(current);
		current = prev;
	}
	*tail = NULL;
}
