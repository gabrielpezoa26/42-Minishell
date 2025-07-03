/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:42:32 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/07/03 15:36:22 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	free_pointers(char *single_pointer, char **double_pointer)
{
	free(single_pointer);
	free_matrix(double_pointer);
}

void	exit_minishell(t_data *data, int exit_code)
{
	if (data)
	{
		if (data->input)
			free(data->input);
		free_tokens(&data->tokens);
		if (data->cmds)
			free_commands(&data->cmds);
		free_env(&data->env);
		free_env(&data->locals);
		free(data);
	}
	rl_clear_history();
	exit(exit_code);
}
