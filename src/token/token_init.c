/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:19:56 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/16 17:06:13 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*str_quote(char *input, char quote)
{
	char	*str;
	char	*temp;

	str = ft_strdup("");
	while (**input != quote)
	{
		if (quote == '\"' && **input == '$')
			*is_BOOM = true;
		temp = ft_join(str, **input);
		free(str);
		str = temp;
		(*input)++;
	}
	(*input)++;
	return (str);
}

static char	*str_operator(char *input, int *redir)
{
	char	*str;
	int		c;

	if (**input == '|')
		*redir = 1;
	else if (**input == '<')
		*redir = 2;
	else if (**input == '>')
		*redir = 3;
	(*input)++;
	if (**input == '>' && *redir == 3)
	{
		*redir = 4;
		(*input)++;
		return (ft_strdup(">>"));
	}
	else if (**input == '<' && *redir == 2)
	{
		*redir = 5;
		(*input)++;
		return (ft_strdup("<<"));
	}
	c = *(*input - 1);
	str = ft_strdup_char(&c);
	return (str);
}

static char *str_string(char **input, bool *is_BOOM)
{
	char	*str;
	char	*temp;

	str = ft_strdup("");
	while (**input && !is_wspace(**input)/* && !is_operator(**input) && !is_quote(**input)*/)
	{
		if (**input == '$')
			*is_BOOM = true;
		temp = ft_join(str, **input);
		free(str);
		str = temp;
		(*input)++;
	}
	return (str);
}

static char	*handle_token(char **input, int *operator)
{
	char	quote;
	char	*str;

	if (**input == '\'' || **input == '\"')
	{
		quote = **input;
		(*input)++;
		str = str_quote(input, quote, is_BOOM);
	}
	else if (is_operator(**input))
		str = str_operator(input, operator);
	else
		str = str_string(input, is_BOOM);
	return (str);
}

/**
 * void init_tokens -> extracts each token initialize them, and
 * 						appends to the list
 * 
 * @tokens: the list to be filled
 * @input: input straight from the command-line
 * 
 * @return: void
 */
void	init_tokens(t_token **tokens, char *input)
{
	char	*str;
	int		operator;
	bool	is_BOOM;

	while (*input)
	{
		is_BOOM = false;
		operator = 0;
		if (is_wspace(*input))
			input++;
		else
		{
			str = handle_token(&input, &operator, &is_BOOM);
			append_node(tokens, str, operator, is_BOOM);
		}
	}
}
