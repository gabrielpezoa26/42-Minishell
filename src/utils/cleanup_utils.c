/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:42:32 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/29 17:44:19 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	clear_history();
	exit(exit_code);
}
