/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:25:52 by fduque-a          #+#    #+#             */
/*   Updated: 2023/12/18 19:13:33 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	This function resets the index's
*/
void	reset_index(t_index *index)
{
	index->i = 0;
	index->j = 0;
	index->k = 0;
	index->squote = 0;
	index->dquote = 0;
}

/*
**	Frees allocated memory for string array
*/
void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

/*
** Frees allocated memory for number matrix 
** array that doesn't end with NULL
*/
void	free_int_matrix(t_shell *shell)
{
	int	i;

	i = -1;
	if (shell == NULL || shell->pipes == NULL)
		return ;
	while (++i < shell->nbr_commands)
		free(shell->pipes[i]);
	free(shell->pipes);
}

/*
**	This function deletes the heredoc files
*/
void	delete_heredoc_list(t_shell *sh)
{
	char	*file;
	int		i;

	i = 0;
	file = ft_calloc(2, sizeof(char));
	file[0] = '.';
	file = ft_strjoin_gnl(file, "q");
	while (!access(file, R_OK) && i++ < sh->heredoc)
	{
		unlink(file);
		file = ft_strjoin_gnl(file, "q");
	}
	free(file);
}

/*
**	This function cleans the tree
*/
void	free_parser_tree(t_tree_node *root)
{
	if (!root)
		return ;
	if (root->cmd && root->cmd[0])
		free_matrix(root->cmd);
	root->cmd = NULL;
	if (root->in_redirs)
		free_lexer_list(root->in_redirs);
	root->in_redirs = NULL;
	if (root->out_redirs)
		free_lexer_list(root->out_redirs);
	root->out_redirs = NULL;
	free_parser_tree(root->left);
	free_parser_tree(root->right);
	free(root);
}
