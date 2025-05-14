/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:19:56 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/14 18:17:16 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*str_quote(char *input, char quote)
{
	char	*str;

	while (*input != quote)
	{
		str = *ft_join(str, *input);
		input++;
	}
	input++;
	return (str);
}

static char	*str_operator(char *input, int *redir)
{
	char	*str;

	if (*input == '|')
		redir = 1;
	else if (*input == '<')
		redir = 2;
	else if (*input == '>')
		redir = 3;
	input++;
	if (*input == '>')
	{
		redir = 4;
		str = ft_strdup(">>");
		input++;
		return (str);
	}
	else if (*input == '<')
	{
		redir = 5;
		str = ft_strdup("<<");
		input++;
		return (str);
	}
	str = ft_strdup_char(redir);
	return (str);
}

void	init_tokens(t_token **tokens, char *input)
{
	char	quote;
	char	*str;
	int		operator;

	str = "";
	operator = 0;
	quote = '\0';
	while (*input || *input != ' ' || *input != '\t')
	{
		if (*input == '\'' || *input == '\"')
		{
			quote = *input;
			str = str_quote(input, quote);
		}
		else if (is_operator(*input))
			str = str_operator(*input, &operator);
		append_node(*tokens, str, operator);
	}
}
