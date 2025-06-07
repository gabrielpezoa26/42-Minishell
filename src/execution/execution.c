/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:50:37 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/07 16:02:42 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * token_to_args -> converts the list of tokens to an **list
 * 
 * @tokens: the list of tokens to be converted
 * 
 * @return: the **list of arguments
 */
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

/**
 * execution -> identifies a built-in and calls the responsible function
 * 
 * @data: a pointer to t_data
 * @tokens: pointer to t_token, lol
 * 
 * @return: true if deu bom
 */
bool	execution(t_data *data, t_token *tokens)
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
	if (ft_strcmp(arg_list[0], "pwd") == 0)
		my_pwd();
	if (ft_strcmp(arg_list[0], "env") == 0)
		my_env(data);
	if (ft_strcmp(arg_list[0], "export") == 0 && arg_list[1])
		my_export(data, arg_list[1]);
	free(arg_list);
	return (true);
}
