/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:23:00 by dteruya           #+#    #+#             */
/*   Updated: 2025/06/04 22:28:35 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*init_token(char	*content, int operator, bool is_expandable)
{
	t_token	*new_token;

	new_token = (t_token *)ft_malloc(sizeof(t_token), sizeof(char));
	new_token->str = ft_strdup(content);
	new_token->type = operator;
	new_token->is_expandable = is_expandable;
	new_token->is_EOF = false;
	new_token->index = 0;
	new_token->next = NULL;
	return (new_token);
}

void	append_token(t_token **tokens, char *content, int op, bool is_expand)
{
	t_token	*token;

	token = init_token(content, op, is_expand);
	if (*tokens == NULL)
		*tokens = token;
	else
		add_back(tokens, token);
}

/**
 * t_token *last_node -> finds the last node from the list and returns it
 *
 * @token: the token at the top of the list
 * 
 * @return: returns the last token
 */
t_token	*last_token(t_token *token)
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
	last = last_token(*token);
	last->next = node;
}
