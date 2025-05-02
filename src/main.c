/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:37:42 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/01 21:56:02 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// trocar o loop
// tratar erros simples argv

int	main(int argc, char **argv, char **envp)
{
	if (!check_input(argc, argv))
		return (1);
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
		--chama o parsa

		--executa
	
		--free
*/