/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:23:00 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/16 15:48:10 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*init_node(char	*content, int operator, bool is_BOOM)
{
	t_token	*new_node;
	int		size;

	new_node = (t_token *)ft_malloc(sizeof(t_token));
	new_node->str = ft_strdup(content);
	new_node->type = operator;
	new_node->is_expandable = is_BOOM;
	new_node->array = NULL;
	if (is_BOOM)
	{
		size = word_count(new_node->str);
		new_node->array = ft_calloc(size, sizeof(int));
		find_money(new_node->array, new_node->str, size);
	}
	new_node->next_token = NULL;
	return (new_node);
}

void	append_node(t_token **tokens, char *content, int operator, bool is_BOOM)
{
	t_token	*node;

	node = init_node(content, operator, is_BOOM);
	if (*tokens == NULL)
		*tokens = node;
	else
		add_back(tokens, node);
}

static t_token	*last_node(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next_token)
		token = token->next_token;
	return (token);
}

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
	last->next_token = node;
}
