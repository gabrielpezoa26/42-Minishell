/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:37:42 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/05 17:40:38 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	minishell_loop(t_mango *mango)
{
	while (1)
	{
		mango->input = readline("minishell$ ");
		if (parse_input(mango))
		{
			printf("DEBUG: executaaaaaa\n");
		}
		mango->input = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mango	*mango;

	mango = malloc(sizeof(mango));
	if (!mango)
		return (1);
	ft_memset(mango, 0, sizeof(t_mango));
	if (!basic_check(argc, argv))
		return (1);
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