/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:41:15 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/12 23:16:21 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	dividir em outras funcoes/arquivos
*/
static void	count_quotes(char *input, int *db, int *sg)
{
	bool	is_open;
	char	quote;

	is_open = false;
	quote = '\0';
	while (*input)
	{
		if (!is_open && (*input == '\'' || *input == '\"'))
		{
			quote = *input;
			if (quote == '\'')
				(*sg)++;
			else
				(*db)++;
			is_open = true;
		}
		else if (quote == *input)
		{
			if (*input == '\'')
				(*sg)++;
			else
				(*db)++;
			is_open = false;
		}
		input++;
	}
}

static bool	are_quotes_valid(char *input)
{
	int		double_q;
	int		single_q;

	double_q = 0;
	single_q = 0;
	count_quotes(input, &double_q, &single_q);
	return (double_q % 2 == 0 && single_q % 2 == 0);
}

static bool	is_invalid_operator(const char *input)
{
	if (input[0] == '|' && input[1] == '|')
		return (true);
	if (input[0] == '>' && input[1] == '>' && input[2] == '>')
		return (true);
	if (input[0] == '<' && input[1] == '<' && input[2] == '<')
		return (true);
	if (input[0] == '<' && input[1] == '>')
		return (true);
	if (input[0] == '>' && input[1] == '<')
		return (true);
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
		if (!in_quote && is_invalid_operator(input))
			return (true);
		input++;
	}
	return (false);
}

bool	to_token(t_data *data)
{
	if (!are_quotes_valid(data->input))
	{
		printf("Error!\n");
		return (false);
	}
	if (token_operators(data->input))
	{
		printf("Error!\n");
		return (false);
	}
	return (true);
}
