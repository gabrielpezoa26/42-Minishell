/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:16:51 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/04 15:27:15 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_structs(t_data *target)
{
	if (target)
		free(target);
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

void	mango_free(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
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

void	free_tokens(t_token **tokens)
{
	t_token	*next_token;

	if (tokens == NULL)
		return ;
	while (*tokens)
	{
		next_token = (*tokens)->next;
		free((*tokens)->str);
		free(*tokens);
		*tokens = next_token;
	}
	*tokens = NULL;
}
