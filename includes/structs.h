/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:35:49 by arepsa            #+#    #+#             */
/*   Updated: 2023/12/08 18:25:26 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

typedef enum s_tokens
{
	WORD,
	PIPE,
	GREAT,
	DOU_GREAT,
	LESS,
	DOU_LESS,
}	t_tokens;

typedef struct s_lexer
{
	char			*str;
	int				i;
	char			*eof;
	t_tokens		operator;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_index
{
	int	i;
	int	j;
	int	k;
	int	dquote;
	int	squote;
}	t_index;

typedef struct s_envlst
{
	char			*key;
	char			*value;
	int				visible;
	struct s_envlst	*next;
}				t_envlst;

typedef struct s_tree_node
{
	int					type;
	char				**cmd;
	t_lexer				*in_redirs;
	t_lexer				*out_redirs;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}	t_tree_node;

typedef struct s_shell
{
	char		*ui;
	char		*home;
	char		*prompt;
	char		*files;
	char		**mini_env;
	int			**pipes;
	char		***cmds;
	int			len;
	int			expanded;
	int			nbr_commands;
	int			fd_in;
	int			fd_out;
	int			pid;
	int			heredoc;
	int			hd_quotes_eof;
	t_index		*index;
	t_envlst	*env_lst;
	t_lexer		*lexer;
	t_tree_node	*parser;
	t_lexer		*heredoc_fd;
}				t_shell;

#endif
