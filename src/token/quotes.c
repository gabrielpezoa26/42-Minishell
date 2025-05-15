/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:04:17 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/14 14:12:30 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	count_quotes(char *input, char quote, int *db, int *sg)
{
	bool	is_open;

	is_open = false;
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

bool	are_quotes_valid(char *input)
{
	int		double_q;
	int		single_q;
	char	quote;

	quote = '\0';
	double_q = 0;
	single_q = 0;
	count_quotes(input, quote, &double_q, &single_q);
	return (double_q % 2 == 0 && single_q % 2 == 0);
}
