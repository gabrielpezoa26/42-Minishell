/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:22:33 by dteruya           #+#    #+#             */
/*   Updated: 2025/06/30 12:49:36 by gcesar-n         ###   ########.fr       */
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

// void	debug_print_tokens(t_token *tokens)
// {
// 	int	i;

// 	i = 0;
// 	while (tokens)
// 	{
// 		ft_printf("DEBUG: Token %d: str='%s' | type=%d | BOOM=%d\n",
// 			i, tokens->str, tokens->type, tokens->is_expandable);
// 		tokens = tokens->next;
// 		i++;
// 	}
// }

static bool	is_all_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!is_wspace(input[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	parse_input(t_data *data, t_token **tokens, t_env **my_envp)
{
	(void)my_envp;
	if (!data->input)
		exit_minishell(data, 0);
	else if (ft_strcmp(data->input, "\0") == 0)
		return (false);
	else if (is_all_spaces(data->input))
		return (true);
	if (!convert_token(data, tokens))
		return (false);
	// debug_print_tokens(*tokens);
	handle_assignments(*tokens, &data->locals);
	return (true);
}
