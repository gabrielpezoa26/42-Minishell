/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:26:16 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/17 23:33:48 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * bool is_tok_op -> checks if it's a operator
 * 
 * @type: the current token
 * 
 * @return: bool
 */
static bool	is_tok_op(t_type type)
{
	return (type == PIPE
		|| type == REDIR_IN
		|| type == REDIR_OUT
		|| type == REDIR_APPEND
		|| type == REDIR_DELIMITER);
}

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

	if (!tokens || !*tokens)
		return (false);
	curr_token = *tokens;
	if (is_tok_op(curr_token->type))
		return (false);
	while (curr_token->next)
	{
		if (is_tok_op(curr_token->type) && is_tok_op(curr_token->next->type))
			return (false);
		curr_token = curr_token->next;
	}
	if (is_tok_op(curr_token->type))
		return (false);
	return (true);
}
