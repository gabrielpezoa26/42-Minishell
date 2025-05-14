/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:23:00 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/14 18:15:06 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*init_node(char	*content, int operator)
{
	t_token	*new_node;

	new_node = (t_token *)ft_malloc(sizeof(t_token));
	new_node->str = ft_strdup(content);
	new_node->type = operator;
	new_node->is_BOOM = false;
	new_node->next_token = NULL;
	return (new_node);
}

void	append_node(t_token **tokens, char *content, int operator)
{
	t_token	*node;

	node = init_node(content, operator);
	if (*tokens == NULL)
		*tokens = node;
	else
		add_back(tokens, node);
}
