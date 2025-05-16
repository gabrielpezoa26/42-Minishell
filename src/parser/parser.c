/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:22:33 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/16 15:52:16 by dteruya          ###   ########.fr       */
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

void	debug_print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		printf("Token %d: str='%s' | type=%d | BOOM=%d\n",
			i, tokens->str, tokens->type, tokens->is_expandable);
		tokens = tokens->next_token;
		i++;
	}
}

void	parse_input(t_data *data, t_token **tokens)
{
	if (!data->input)
		exit_minishell(data, "DEBUG: finishhhh");
	if (ft_strcmp(data->input, "\0") == 0 || verify_space(data->input))
	{
		data->exec = false;
		return ;
	}
	if (!to_token(data, tokens))
	{
		data->exec = false;
		return ;
	}
	debug_print_tokens(*tokens);
}
