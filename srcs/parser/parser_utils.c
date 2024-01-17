/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:42:16 by fduque-a          #+#    #+#             */
/*   Updated: 2023/12/13 20:13:56 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	Save heredoc file descriptor in the tree
*/
void	handle_heredoc(t_shell *sh, t_lexer **in_redirs)
{
	t_lexer		*tmp;

	tmp = sh->heredoc_fd;
	sh->heredoc_fd = sh->heredoc_fd->next;
	tmp->next = NULL;
	lexer_add_back(in_redirs, tmp);
}

/*
**	Add redirection nodes to the new list
*/
void	in_redir_aux(t_lexer **redirs, t_lexer *tmp, int i, t_shell *sh)
{
	t_lexer	*new;

	new = lexer_new(ft_strdup(tmp->next->str), i, sh);
	new->operator = tmp->operator;
	lexer_add_back(redirs, new);
}

/*
** Removes input redirections from lexer linked list
** and creates a new linked list (type t_lexer)
*/
void	handle_in_redir(t_lexer **start, t_lexer *end, \
		t_lexer **in, t_shell *sh)
{
	int		i;
	t_lexer	*tmp;
	t_lexer	*tmp_to_delete;

	i = 0;
	tmp = *start;
	while (tmp && tmp->next && tmp != end)
	{
		if (tmp->next && (tmp->operator == LESS))
			in_redir_aux(in, tmp, i++, sh);
		else if (tmp->next && (tmp->operator == DOU_LESS))
			handle_heredoc(sh, in);
		if (tmp->operator == LESS || tmp->operator == DOU_LESS)
		{
			tmp_to_delete = tmp;
			tmp = tmp->next->next;
			lexer_delone(start, tmp_to_delete->i);
		}
		if (tmp && tmp->next && tmp->operator < LESS && tmp != end)
			tmp = tmp->next;
	}
}

/*
** Removes output redirections from lexer linked list
** and creates a new linked list (type t_lexer)
*/
void	handle_out_redir(t_lexer **start, t_lexer *end, \
		t_lexer **out, t_shell *sh)
{
	int		i;
	t_lexer	*tmp;
	t_lexer	*tmp_to_delete;
	t_lexer	*new_o_redir;

	i = 0;
	tmp = *start;
	while (tmp != end)
	{
		if (tmp->next && (tmp->operator == GREAT || tmp->operator == DOU_GREAT))
		{
			new_o_redir = lexer_new(ft_strdup(tmp->next->str), i++, sh);
			new_o_redir->operator = tmp->operator;
			lexer_add_back(out, new_o_redir);
			tmp_to_delete = tmp;
			tmp = tmp->next->next;
			lexer_delone(start, tmp_to_delete->i);
			if (!tmp)
				break ;
		}
		else if (tmp != end)
			tmp = tmp->next;
	}
}

/*
**	Creates a tree node of type CMD that contains a 
** linked list of redirections and a char ** of arguments
*/
t_tree_node	*command_node(t_lexer **start, t_lexer *end, t_shell *sh)
{
	t_tree_node	*cmd_node;

	cmd_node = ft_calloc(1, sizeof(t_tree_node));
	cmd_node->type = CMD;
	handle_in_redir(start, end, &(cmd_node->in_redirs), sh);
	handle_out_redir(start, end, &(cmd_node->out_redirs), sh);
	if (*start != end)
		list_to_array(*start, end, &(cmd_node->cmd));
	return (cmd_node);
}
