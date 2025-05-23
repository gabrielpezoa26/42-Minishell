/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:41:15 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/23 12:07:04 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	convert_token(t_data *data, t_token **tokens, char **my_envp)
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
	search_dollar(tokens, my_envp);
	return (true);
}
