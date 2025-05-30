/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:22:33 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/30 13:36:28 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_argc(int argc)
{
	if (argc != 1)
	{
		printf("Invalid argument count :(( \n");
		return (false);
	}
	return (true);
}

void	debug_print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		ft_printf("DEBUG: Token %d: str='%s' | type=%d | BOOM=%d\n",
			i, tokens->str, tokens->type, tokens->is_expandable);
		tokens = tokens->next;
		i++;
	}
}

/**
 * parse_input - validates and tokenizes the user input string
 * 
 * @data: pointer to the main struct
 * @tokens: pointer to the token list
 * 
 * @return: void
 */
bool	parse_input(t_data *data, t_token **tokens, t_env **my_envp)
{
	bool	flag;

	flag = true;
	if (!data->input)
		exit_minishell(data, "DEBUG: finishhhh");
	if (ft_strcmp(data->input, "\0") == 0 || verify_space(data->input))
		flag = false;
	if (!convert_token(data, tokens, my_envp))
		flag = false;
	debug_print_tokens(*tokens);
	if (flag == true)
		add_history(data->input);
	return (flag);
}
