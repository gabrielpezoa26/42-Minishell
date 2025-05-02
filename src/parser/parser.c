/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:22:33 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/02 16:43:28 by gcesar-n         ###   ########.fr       */
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

bool	basic_check(int argc, char **argv)
{
	char	*rl;

	if (argc != 1)
	{
		ft_printf("Invalid arguments count :(( \n");
		return (false);
	}
	return (true);
}
