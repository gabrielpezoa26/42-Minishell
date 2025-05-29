/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:41:15 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/29 17:17:14 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void print_error(void *ptr)
// {
// 	char	type;

// 	type = &ptr;
// 	if (type == '|')
// 		printf("bash: syntax error near unexpected token `|'\n");
// 	if (type == '>')
// 		printf("bash: syntax error near unexpected token `>'\n");
// 	if (type == '<')
// 		printf("bash: syntax error near unexpected token `<'\n");
// }

bool	convert_token(t_data *data, t_token **tokens)
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
	init_tokens(tokens, data->input);
	if (!validate_tokens(tokens))
	{
		printf("%s\n", TOKEN);
		return (false);
	}
	search_dollar(data, tokens);
	return (true);
}
