/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:07:49 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/16 17:39:44 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_cmd	*init_cmd_node(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirections = NULL;
	cmd->next = NULL;
	return (cmd);
}

static void	parse_redirection(t_token **tokens, t_cmd *cmd)
{
	t_redir	*redir;
	t_list	*new_node;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return ;
	redir->type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (*tokens && (*tokens)->type == WORD)
	{
		redir->file = ft_strdup((*tokens)->str);
	}
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		free(redir);
		return ;
	}
	new_node = ft_lstnew(redir);
	ft_lstadd_back(&cmd->redirections, new_node);
}

static int	count_args(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == WORD)
			count++;
		else
			tokens = tokens->next;
		if (tokens)
			tokens = tokens->next;
	}
	return (count);
}

static void	parse_simple_command(t_token **tokens, t_cmd *current_cmd)
{
	int	i;

	current_cmd->args = ft_calloc(count_args(*tokens) + 1, sizeof(char *));
	if (!current_cmd->args)
		return ;
	i = 0;
	while (*tokens && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == WORD)
			current_cmd->args[i++] = ft_strdup((*tokens)->str);
		else
			parse_redirection(tokens, current_cmd);
		if (*tokens)
			*tokens = (*tokens)->next;
	}
}

/**
 * @brief Parses a list of tokens into a linked list of command structures.
 *
 * This function iterates through the token list, creating a new command node
 * for each sequence of tokens separated by a PIPE.
 *
 * @param tokens The head of the token list.
 * @return The head of the newly created command list (`t_cmd *`).
 */
t_cmd	*parser(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*current_cmd;

	if (!tokens)
		return (NULL);
	head = init_cmd_node();
	current_cmd = head;
	while (tokens)
	{
		parse_simple_command(&tokens, current_cmd);
		if (tokens)
		{
			current_cmd->next = init_cmd_node();
			current_cmd = current_cmd->next;
			tokens = tokens->next;
		}
	}
	return (head);
}
