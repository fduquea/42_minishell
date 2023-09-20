/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:10:24 by fduque-a          #+#    #+#             */
/*   Updated: 2023/09/20 15:34:06 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lexer.h"
# include "../libft/include/libft.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>

typedef struct s_index
{
    int	i;
    int	j;
    int	k;
}	t_index;

typedef struct s_shell
{
    t_index     index;
    // char		*mini_env;
	// t_envlst	*env_lst;
    t_lexer     *lexer;
    char        *ui;
//    t_parser	*parser;
}            t_shell;

void ft_lexer(t_shell **shell, char *command_buffer);

#endif // MINISHELL_H
