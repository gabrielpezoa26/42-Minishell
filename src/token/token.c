/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:41:15 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/12 18:22:37 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	count_quotes(char *input, int *db, int *sg)
{
	bool	flag;
	char	quote;

	flag = false;
	while (*input)
	{
		if (!flag && (*input == '\'' || *input == '\"'))
		{
			quote = *input;
			if (quote == '\'')
				(*sg)++;
			else
				(*db)++;
			flag = true;
		}
		else if (quote == *input)
		{
			if (*input == '\'')
				(*sg)++;
			else
				(*db)++;
			flag = false;
		}
		input++;
	}
}

bool	verify_quotes(char *input)
{
	int		double_q;
	int		single_q;

	double_q = 0;
	single_q = 0;
	count_quotes(input, &double_q, &single_q);
	return (double_q % 2 == 0 && single_q % 2 == 0);
}

bool	token_operators(char *input)
{
	bool	flag;
	int i = 0;
	
	flag = false;
	while (*input)
	{
		if (!flag && *input == '\'' || *input == '\"')
			flag = true;
		else if (*input == '\'' || *input == '\"')
			flag = false;
		
		input++;	
	}
	return (false);
}

void	to_token(t_data *data)
{
	if (!verify_quotes(data->input))
		printf("Error!\n");
	if (!token_operators(data->input))
		printf("Error!\n");
}
