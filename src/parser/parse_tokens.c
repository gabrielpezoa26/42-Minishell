/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:26:16 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/22 12:37:47 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * bool parse_tokens -> checks if input starts or ends with operators
 * 
 * @input: list of already tokenized items
 * 
 * @return: bool
 */
bool	validate_tokens(t_token **tokens)
{
	t_token	*curr_token;
	t_token	*last_token;

	if (!tokens || !*tokens)
		return (false);
	curr_token = *tokens;
	last_token = last_node(*tokens);
	if (curr_token->type > 0)
		return (false);
	if (last_token->type > 0)
		return (false);
	while (curr_token->next)
	{
		if (curr_token->type == 1 && curr_token->next->type == 1)
			return (false);
		curr_token = curr_token->next;
	}
	return (true);
}
