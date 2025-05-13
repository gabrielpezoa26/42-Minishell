/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:41:15 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/13 16:43:16 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	to_token(t_data *data)
{
	if (!are_quotes_valid(data->input))
	{
		printf("%s\n", TOKEN);
		return (false);
	}
	if (token_operators(data->input))
	{
		printf("%s\n", TOKEN);
		return (false);
	}
	return (true);
}
