/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:41:15 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/17 17:35:01 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	cpa aqui poe o parse_tokens()
*/
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
	return (true);
}
