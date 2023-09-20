/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:28:04 by fduque-a          #+#    #+#             */
/*   Updated: 2023/09/20 15:22:22 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


// Print the lexer linked list's words

void	print_lexer(t_lexer *lexer)
{
	while (lexer)
	{
		printf("String : %s\n", lexer->str);
		printf("Token : %d\n", lexer->token);
		printf("Index : %d\n", lexer->i);
		lexer = lexer->next;
	}
}

void ft_loop(t_shell **shell)
{
    while (1) // add global variable to exit
    {
        (*shell)->ui = readline("minishell$ ");
		if ((*shell)->ui)
		{
			add_history((*shell)->ui);
        	ft_lexer(shell, (*shell)->ui);
			print_lexer((*shell)->lexer);
		}
    }
}

int main(int argc, char **argv, char **envp)
{
    t_shell *shell;
    if (argc != 1 || argv[1])
	{
		printf("Am I really seeing an argument there?!\n'./minishell' is the only valid call kid.\n");
		exit(0);
	}
    shell = ft_calloc(1, sizeof(t_shell));
//    shell->mini_env = copy_env(envp);
    ft_loop(&shell);
    if (envp[0] == NULL)
        return (0);
}
