/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:35:49 by dteruya           #+#    #+#             */
/*   Updated: 2025/06/10 20:12:05 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_cmd_args(t_token *temp)
{
	int	arg_count;

	arg_count = 1;
	while (temp && temp->type == WORD)
	{
		arg_count++;
		temp = temp->next;
	}
	return (arg_count + 1);
}

static void	cmd_args(t_cmd *cmd, t_token *token)
{
	int	i;

	i = 0;
	cmd->args[i++] = ft_strdup(cmd->name);
	while (token && token->type == WORD)
	{
		cmd->args[i] = ft_strdup(token->str);
		token = token->next;
		i++;
	}
	cmd->args[i] = NULL;
}

static void	cmd_redir(t_cmd *cmd, t_token *token)
{
	while (token)
	{
		if (token->type == REDIR_OUT)
		{
			cmd->out_file = ft_strdup(token->next->str);
			token = token->next->next;
		}
		else if (token->type == REDIR_APPEND)
		{
			cmd->out_file = ft_strdup(token->next->str);
			cmd->append = 1;
			token = token->next->next;
		}
		else if (token->type == REDIR_IN)
		{
			cmd->in_file = ft_strdup(token->next->str);
			token = token->next->next;
		}
		else
			token = token->next;
	}
}

t_cmd	*init_cmd(t_token *tokens)
{
	t_cmd	*cmd;
	t_token	*current;
	t_token	*temp;

	current = tokens;
	cmd = (t_cmd *)ft_malloc(sizeof(t_cmd), sizeof(char));
	cmd->name = ft_strdup(current->str);
	cmd->out_file = NULL;
	cmd->in_file = NULL;
	cmd->append = 0;
	cmd->next = NULL;
	tokens = tokens->next;
	temp = tokens;
	cmd->args = ft_malloc(count_cmd_args(temp), sizeof(char *));
	cmd_args(cmd, temp);
	cmd_redir(cmd, current);
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*last_cmd(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}
void	add_back_cmd(t_cmd **cmd, t_cmd *node)
{
	t_cmd	*last;

	if (cmd == NULL || node == NULL)
		return ;
	if (*cmd == NULL)
	{
		*cmd = node;
		return ;
	}
	last = last_cmd(*cmd);
	last->next = node;
}

void	append_cmd(t_cmd **cmds, t_token *tokens)
{
	t_cmd	*cmd;

	cmd = init_cmd(tokens);
	if (*cmds == NULL)
		*cmds = cmd;
	else
		add_back_cmd(cmds, cmd);
}
