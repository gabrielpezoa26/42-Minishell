/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:16:51 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/10 20:14:39 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_structs(t_data *target)
{
	if (target)
		free(target);
}

void free_cmd(t_cmd **cmds)
{
	t_cmd	*next;
	int i;

	if (cmds == NULL)
		return ;
	while (*cmds)
	{
		i = 0;
		next = (*cmds)->next;
		free((*cmds)->name);
		while((*cmds)->args[i])
		{
			free((*cmds)->args[i]);
			i++;
		}
		free((*cmds)->args); 
		free(*cmds);
		*cmds = next;
	}
	*cmds = NULL;
	
}

void	free_env(t_env **my_env)
{
	t_env	*next;

	if (my_env == NULL)
		return ;
	while (*my_env)
	{
		next = (*my_env)->next;
		free((*my_env)->str);
		free(*my_env);
		*my_env = next;
	}
	*my_env = NULL;
}

/**
 * exit_minishell - free's the structs and call's exit(1)
 * 
 * @data: pointer to the main struct
 * @message: message to be printed
 * 
 * @return: void
 */
void	exit_minishell(t_data *data, char *message)
{
	free_structs(data);
	printf("%s\n", message);
	exit(1);
}
