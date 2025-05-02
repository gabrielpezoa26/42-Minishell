/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:22:33 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/01 21:52:55 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	check_input:
		--verifica argc
		--add_history
		--trata aspas
		--tokeniza
		--cria os comandos
		--expande variavel*
*/
bool	check_input(int argc, char **argv)
{
	char	*rl;

	if (argc != 1)
	{
		ft_printf("Invalid arguments count :(( \n");
		return (false);
	}
	while (1)
	{
		rl = readline("minishell$ ");
		if (rl)
		{
			ft_printf("%s\n", rl);
			add_history(rl);
			free(rl);
		}
		else
			exit(0);
	}
	return (true);
}
