/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 17:28:21 by arepsa            #+#    #+#             */
/*   Updated: 2023/12/18 17:39:14 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_empty_line(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (!str[i])
		return (true);
	return (false);
}

/* Ctrsl + D error */
void	handle_empty_line_exit(t_shell *sh, int fd)
{
	printf("%s\nexit\n", \
	"minishell: syntax error: unexpected end of file");
	close(fd);
	clear_shell(sh);
	exit(3);
}

/* just pipe symbol error */
void	handle_just_pipe(t_shell *sh, char *str)
{
	char	*no_spaces;

	if (!str)
		return ;
	no_spaces = ft_strtrim(str, WHITESPACE);
	if (no_spaces[0] == '|')
	{
		printf("%s\n", "minishell: syntax error near unexpected token `|'");
		free(str);
		g_exit = 2;
		reset_loop(sh);
	}
	free(no_spaces);
}
