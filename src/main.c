/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:37:42 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/26 10:34:46 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * minishell_loop - reads, parses and prepares for execution
 * 
 * @data: pointer to the main struct
 * 
 * @return: void
 */
static void	minishell_loop(t_data *data, char **my_envp)
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
		parse_input(data, &tokens, my_envp);
		if (data->exec)
			printf("DEBUG: executaaaaaa\n");
		free_tokens(&tokens);
		free(data->input);
		data->input = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	**my_env;

	(void)argv;
	my_env = ft_malloc(count_rows(envp) + 1, sizeof(char *));
	env_dup(envp, my_env);
	data = ft_calloc(1, sizeof(t_data));
	if (!check_argc(argc))
		return (1);
	minishell_loop(data, my_env);
	free(data);
	mango_free(my_env);
	return (0);
}
