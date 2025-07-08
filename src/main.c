/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:37:42 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/07/07 22:55:20 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	minishell_loop(t_data *data)
{
	while (1)
	{
		setup_interactive_signals();
		data->input = readline("minishell$ ");
		if (!data->input)
			break ;
		if (*data->input && !is_all_spaces(data->input))
			add_history(data->input);
		data->tokens = NULL;
		data->cmds = NULL;
		data->exec = true;
		if (parse_input(data, &data->tokens, &data->env))
		{
			if (!handle_heredocs(&data->tokens, data))
				data->exec = false;
			if (data->exec)
			{
				data->cmds = parser(data->tokens);
				if (data->cmds)
					data->last_exit_status = execution(data->cmds, data);
			}
		}
		free_minishell_loop(data);
		data->input = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	if (!check_argc(argc))
		return (1);
	data = ft_calloc(1, sizeof(t_data));
	get_data(true, data);
	data->env = NULL;
	env_dup(envp, &data->env);
	data->locals = NULL;
	minishell_loop(data);
	exit_minishell(data, data->last_exit_status);
	return (0);
}
