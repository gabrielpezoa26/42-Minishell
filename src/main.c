/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:37:42 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/15 17:23:24 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	minishell_loop(t_data *data)
{
	t_token	*tokens;

	while (1)
	{
		data->exec = true;
		data->input = readline("minishell$ ");
		if (!data->input)
			break ;
		if (*data->input)
			add_history(data->input);
		tokens = NULL;
		parse_input(data, &tokens);
		if (data->exec)
			printf("DEBUG: executaaaaaa\n");
		free(data->input);
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
valgrind --suppressions=readline.supp ./minishell
*/