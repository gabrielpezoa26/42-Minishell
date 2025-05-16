/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:04:15 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/15 22:03:23 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * bool is_invalid_operator -> validates the operators (no "||", ">>>", "<<")
 * 
 * @input: operator to be validated
 * 
 * @return: bool 
 */
static bool	is_invalid_operator(const char *input)
{
	if (input[0] == '|'
		&& (input[1] == '|' || input[1] == '>' || input[1] == '<'))
		return (true);
	if (input[0] == '>')
	{
		if ((input[1] == '|' || input[1] == '<')
			|| (input[1] == '>' && input[2] == '>'))
			return (true);
	}
	if (input[0] == '<')
	{
		if ((input[1] == '|') || input[1] == '>'
			|| (input[1] == '<' && input[2] == '<'))
			return (true);
	}
	return (false);
}

/**
 * bool is_operator -> detects any operator(valid or invalid) then validates it
 * 
 * @input: the prompt to be scanned for operators
 * 
 * @return: bool
 */
static bool	is_operators(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
			return (is_invalid_operator(input));
		i++;
	}
	return (false);
}

/**
 * bool token_operators -> reads the prompt looking for operatorns in general
 * 						(either valid or invalid) and calls the helper funcs
 * 
 * @input: the prompt from the command-line
 * 
 * @return: bool
 */
bool	token_operators(char *input)
{
	bool	in_quote;
	char	quote;

	in_quote = false;
	quote = '\0';
	while (*input)
	{
		if (!in_quote && (*input == '\'' || *input == '\"'))
		{
			in_quote = true;
			quote = *input;
		}
		else if (in_quote && *input == quote)
			in_quote = false;
		if (!in_quote && is_operators(input))
			return (true);
		input++;
	}
	return (false);
}
