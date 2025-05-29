/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_nodes_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:12:58 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/29 17:13:16 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens(t_token **tokens)
{
	t_token	*next_token;

	if (tokens == NULL)
		return ;
	while (*tokens)
	{
		next_token = (*tokens)->next;
		free((*tokens)->str);
		free(*tokens);
		*tokens = next_token;
	}
	*tokens = NULL;
}
