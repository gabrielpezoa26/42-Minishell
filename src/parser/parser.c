/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:22:33 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/01 16:47:19 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int validate_input(char **argv)
{
	char *rl;

	while(1)
	{
		rl = readline("minishell$ ");
		if (rl)
		{
			ft_printf("%s\n", rl);
			add_history(rl);
		}
		else
			exit(0);
	}
	return (1);
}
