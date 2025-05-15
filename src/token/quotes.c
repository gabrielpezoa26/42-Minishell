/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:04:17 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/15 18:48:46 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * void count_quotes - counts all single and double quotes in the prompt
 * 
 * @input: input from command-line
 * @quote: "holds" the current char being counted
 * @db: amount of double quotes
 * @db: amount of single quotes
 * 
 * @return: void (bc it directly increments the respective pointers)
 */
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

/**
 * bool are_quotes_valid - determines if the quotes are valid (properly closed)
 * 
 * @input: input from command-line
 * 
 * @return: bool 
 */
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
