/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:41:15 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/14 15:50:03 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	to_token(t_data *data, t_token **tokens)
{
	if (!are_quotes_valid(data->input) || token_operators(data->input))
	{
		printf("%s\n", TOKEN);
		return (false);
	}
	while (*(data->input)) // percorre toda a string
	{
		if (*(data->input) == ' ' || *(data->input) == '\t') // pula os espaços e tabs
			data->input++;
		else if (*(data->input))
			init_tokens(tokens, data->input); // tudo que não for espaço ou tab
	}
	return (true);
}
