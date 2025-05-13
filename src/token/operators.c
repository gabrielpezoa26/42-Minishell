/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:04:15 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/13 15:08:11 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		if ((input[1] == '|') || (input[1] == '<' && input[2] == '<'))
			return (true);
	}
	return (false);
}

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
