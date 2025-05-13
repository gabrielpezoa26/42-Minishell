/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:22:33 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/13 12:12:14 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_argc(int argc)
{
	if (argc != 1)
	{
		printf("Invalid argument count :(( \n");
		return (false);
	}
	return (true);
}

void	parse_input(t_data *data)
{
	if (data->input == NULL)
		exit_minishell(data, "DEBUG: finishhhh");
	else if (ft_strcmp(data->input, "\0") == 0)
	{
		printf("DEBUG: eh nulo\n");
		data->exec = false;
	}
	else if (verify_space(data->input))
	{
		printf("DEBUG: eh espaço\n");
		data->exec = false;
	}
	if (!to_token(data))
		data->exec = false;
	add_history(data->input);
}
