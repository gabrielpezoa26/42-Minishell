/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:16:51 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/23 15:46:36 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mango_free(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

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
			mango_free(current->args);
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

void	exit_minishell(t_data *data, char *message)
{
	if (data)
	{
		if (data->input)
			free(data->input);
		free_env(&data->env);
		free_env(&data->locals);
		free(data);
	}
	if (message)
		ft_putstr_fd(message, 2);
	clear_history();
	exit(1);
}
