/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:50:37 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/01 23:00:49 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**tokens_to_args(t_token *tokens)
{
	t_token	*temp;
	char	**args;
	int		count;
	int		i;

	i = 0;
	count = 0;
	temp = tokens;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	temp = tokens;
	while (i < count)
	{
		args[i] = temp->str;
		temp = temp->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

bool	execution(t_token *tokens)
{
	char	**arg_list;

	arg_list = tokens_to_args(tokens);
	if (!arg_list || !arg_list[0])
	{
		free(arg_list);
		return (false);
	}
	if (ft_strcmp(arg_list[0], "echo") == 0)
		my_echo(arg_list);
	free(arg_list);
	return (true);
}
