/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nodes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:10:25 by dteruya           #+#    #+#             */
/*   Updated: 2025/06/16 15:45:02 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	count_cmd_args(t_token *temp)
// {
// 	int	arg_count;

// 	arg_count = 1;
// 	while (temp && temp->type == WORD)
// 	{
// 		arg_count++;
// 		temp = temp->next;
// 	}
// 	return (arg_count + 1);
// }

// void	cmd_args(t_cmd *cmd, t_token *token)
// {
// 	int	i;

// 	i = 0;
// 	cmd->args[i++] = ft_strdup(cmd->name);
// 	while (token && token->type == WORD)
// 	{
// 		cmd->args[i] = ft_strdup(token->str);
// 		token = token->next;
// 		i++;
// 	}
// 	cmd->args[i] = NULL;
// }

// void	cmd_redir(t_cmd *cmd, t_token *token)
// {
// 	while (token)
// 	{
// 		if (token->type == REDIR_OUT)
// 		{
// 			cmd->out_file = ft_strdup(token->next->str);
// 			token = token->next->next;
// 		}
// 		else if (token->type == REDIR_APPEND)
// 		{
// 			cmd->out_file = ft_strdup(token->next->str);
// 			cmd->append = 1;
// 			token = token->next->next;
// 		}
// 		else if (token->type == REDIR_IN)
// 		{
// 			cmd->in_file = ft_strdup(token->next->str);
// 			token = token->next->next;
// 		}
// 		else
// 			token = token->next;
// 	}
// }
