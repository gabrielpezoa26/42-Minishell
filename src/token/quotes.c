/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:04:17 by dteruya           #+#    #+#             */
/*   Updated: 2025/07/02 12:46:32 by gcesar-n         ###   ########.fr       */
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

char	*append_until_quote(char **input, char *str, char quote)
{
	char	*tmp;

	while (**input != quote)
	{
		tmp = ft_join(str, **input);
		if (!tmp)
			return (NULL);
		free(str);
		str = tmp;
		(*input)++;
	}
	return (str);
}

void	handle_all_quotes(void)
{
	printf("Command '' not found \n");
}
