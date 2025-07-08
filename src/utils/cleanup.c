/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:16:51 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/07/08 18:12:15 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_redirection(void *content)
{
	t_redir	*redir;

	if (!content)
		return ;
	redir = (t_redir *)content;
	if (redir->file)
		free(redir->file);
	free(redir);
}

void	free_commands(t_cmd **commands)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!commands || !*commands)
		return ;
	current = *commands;
	while (current)
	{
		next = current->next;
		if (current->args)
			free_matrix(current->args);
		if (current->redirections)
			ft_lstclear(&current->redirections, free_redirection);
		free(current);
		current = next;
	}
	*commands = NULL;
}

void	free_env(t_env **my_env)
{
	t_env	*next;

	if (my_env == NULL)
		return ;
	while (*my_env)
	{
		next = (*my_env)->next;
		if ((*my_env)->str)
			free((*my_env)->str);
		free(*my_env);
		*my_env = next;
	}
	*my_env = NULL;
}

void	free_child(t_data *data, int exit_code)
{
	if (data)
	{
		printf("OIIIIIIIIIIIIIIIIIIIIIIIIIIII\n");
		free_tokens(&data->tokens);
		if (data->cmds)
			free_commands(&data->cmds);
		free_env(&data->env);
		free_env(&data->locals);
		if (data->input)
			free(data->input);
		free(data);
	}
	exit(exit_code);
}
