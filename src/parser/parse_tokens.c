/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:26:16 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/31 00:24:18 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	validate_tokens(t_token **tokens)
{
	t_token	*current_t;
	t_token	*last_t;

	if (!tokens || !*tokens)
		return (false);
	current_t = *tokens;
	last_t = last_token(*tokens);
	if (current_t->type > 0)
		return (false);
	if (last_t->type > 0)
		return (false);
	while (current_t->next)
	{
		if (current_t->type == REDIR_DELIMITER && current_t->next->is_expandable)
		{
			current_t->next->is_expandable = false;
			current_t->next->is_EOF = true;
		}
		if (current_t->type == 1 && current_t->next->type == 1)
			return (false);
		current_t = current_t->next;
	}
	return (true);
}
