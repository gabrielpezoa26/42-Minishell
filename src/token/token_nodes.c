/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:23:00 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/26 10:54:26 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*init_node(char	*content, int operator, bool is_expandable)
{
	t_token	*new_node;

	new_node = (t_token *)ft_malloc(sizeof(t_token), sizeof(char));
	new_node->str = ft_strdup(content);
	new_node->type = operator;
	new_node->is_expandable = is_expandable;
	new_node->index = 0;
	new_node->next = NULL;
	return (new_node);
}

void	append_node(t_token **tokens, char *content, int op, bool is_expand)
{
	t_token	*node;

	node = init_node(content, op, is_expand);
	if (*tokens == NULL)
		*tokens = node;
	else
		add_back(tokens, node);
}

/**
 * t_token *last_node -> finds the last node from the list and returns it
 *
 * @token: the token at the top of the list
 * 
 * @return: returns the last token
 */
t_token	*last_node(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}

/**
 * void add_back -> adds the given token at the end of the list
 *
 * @tokens: the list of the tokens
 * @node: the token to be added
 * 
 * @return: void
 */
void	add_back(t_token **token, t_token *node)
{
	t_token	*last;

	if (token == NULL || node == NULL)
		return ;
	if (*token == NULL)
	{
		*token = node;
		return ;
	}
	last = last_node(*token);
	last->next = node;
}
