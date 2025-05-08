/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:37:42 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/08 03:50:44 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	minishell_loop(t_data *data)
{
	while (1)
	{
		data->input = readline("minishell$ ");
		if (parse_input(data))
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