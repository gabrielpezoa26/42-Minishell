/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:37:42 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/03 16:59:45 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//parse_input();
static void	minishell_loop(t_mango *mango)
{
	char	*rl;

	mango = NULL;
	parse_input(mango);
	while (1)
	{
		rl = readline("minishell$ ");
		if (rl)
		{
			printf("%s\n", rl);
			add_history(rl);
			free(rl);
		}
		else
			exit(0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mango	*mango;

	if (!basic_check(argc, argv))
	{
		printf("vishh\n");
		return (1);
	}
	minishell_loop(mango);
	return (0);
}

/*
	--lexer
		trata erros basicos
		transforma o input em tokens

	--parser
		lê os tokens e valida

	--init
		sla

	--exec
		sla
*/

/*
	na main:
		--chama o parser

		--loop
	
		--free


	valgrind --suppressions=mango.supp ./minishell

*/