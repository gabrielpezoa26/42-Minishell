/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:22:33 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/14 14:23:16 by dteruya          ###   ########.fr       */
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

void	parse_input(t_data *data, t_token **tokens)
{
	if (data->input == NULL)
		exit_minishell(data, "DEBUG: finishhhh");
	else if (ft_strcmp(data->input, "\0") == 0)
		data->exec = false;
	else if (verify_space(data->input))
		data->exec = false;
	if (!to_token(data, tokens))
		data->exec = false;
	add_history(data->input);
}
