/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:37:42 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/17 16:31:34 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * minishell_loop - reads, parses and prepares for execution
 * 
 * @data: pointer to the main struct
 * @my_env:
 * 
 * @return: void
 */

static void	minishell_loop(t_data *data, t_env **my_env)
{
	while (1)
	{
		data->input = readline("minishell$ ");
		if (!data->input)
			break ;
		if (*data->input)
			add_history(data->input);
		data->tokens = NULL;
		if (parse_input(data, &data->tokens, my_env))
		{
			handle_heredocs(&data->tokens, *my_env);
			execution(data, data->tokens);
		}
		cleanup_heredocs(data->tokens);
		free_tokens(&data->tokens);
		free(data->input);
		data->input = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	t_env	*my_env;

	(void)argv;
	if (!check_argc(argc))
		return (1);
	setup_interactive_signals();
	data = ft_calloc(1, sizeof(t_data));
	my_env = NULL;
	env_dup(envp, &my_env);
	data->env = my_env;
	data->locals = NULL;
	minishell_loop(data, &my_env);
	free_env(&data->locals);
	free_env(&my_env);
	free(data);
	return (0);
}
