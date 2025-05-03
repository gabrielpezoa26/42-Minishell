/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:22:33 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/03 16:59:28 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	basic_check(int argc, char **argv)
{
	char	*rl;

	if (argc != 1)
	{
		printf("Invalid arguments count :(( \n");
		return (false);
	}
	return (true);
}
#include <stdio.h>

bool	parse_input(t_mango *mango)
{
	if (mango == NULL)
		return (false);
	else if (verify_space(mango->input))
	{
		printf("vishh");
		return (false);
	}
	else if (ft_strcmp(mango->input, "\0") == 0)
		return (false);
	return (true);
}

/*
	check_input:
		--verifica argc
		--add_history
		--trata aspas
		--tokeniza
		--cria os comandos
*/