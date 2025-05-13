/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:37:42 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/13 12:20:25 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	minishell_loop(t_data *data)
{
	while (1)
	{
		data->exec = true;
		data->input = readline("minishell$ ");
		parse_input(data);
		if (data->exec)
		{
			printf("DEBUG: executaaaaaa\n");
		}
		data->input = NULL;
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;

	(void)argv;
	data = ft_calloc(1, sizeof(t_data));
	if (!check_argc(argc))
		return (1);
	minishell_loop(data);
	return (0);
}

/*
	leaks readline():
		valgrind --suppressions=mango.supp ./minishell
*/