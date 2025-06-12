/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:35:49 by dteruya           #+#    #+#             */
/*   Updated: 2025/06/12 18:54:16 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
