/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:37:42 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/07 22:41:47 by gcesar-n         ###   ########.fr       */
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
/*
	TODO: trocar malloc pelo ft_malloc
*/

int	main(int argc, char **argv, char **envp)
{
	t_mango	*mango;

	mango = malloc(sizeof(t_mango));
	if (!mango)
		return (1);
	ft_memset(mango, 0, sizeof(t_mango));
	if (!basic_check(argc, argv))
		return (1);
	minishell_loop(mango);
	return (0);
}

/*
	leaks readline():
		valgrind --suppressions=mango.supp ./minishell
*/