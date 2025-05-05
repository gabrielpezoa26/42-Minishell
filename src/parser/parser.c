/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:22:33 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/05 17:40:57 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	basic_check(int argc, char **argv)
{
	char	*rl;

	if (argc != 1)
	{
		printf("Invalid argument count :(( \n");
		return (false);
	}
	return (true);
}

bool	parse_input(t_mango *mango)
{
	if (mango->input == NULL)
		exit_minishell(mango, "finished");
	else if (ft_strcmp(mango->input, "\0") == 0)
	{
		printf("DEBUG: eh nulo");
		return (false);
	}
	else if (verify_space(mango->input))
	{
		printf("DEBUG: eh espaço\n");
		return (false);
	}
	add_history(mango->input);
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