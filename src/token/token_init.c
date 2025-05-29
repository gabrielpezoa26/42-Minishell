/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:19:56 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/29 18:20:03 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*str_quote(char **input, char quote, bool *is_expandable)
{
	char	*str;
	char	*temp;

	*is_expandable = false;
	str = ft_strdup("");
	while (**input && **input != quote)
	{
		if (quote == '\"' && **input == '$'
			&& *(*input + 1) && char_expandable(*(*input + 1)))
			*is_expandable = true;
		temp = ft_join(str, **input);
		free(str);
		str = temp;
		(*input)++;
	}
	if (**input == quote)
		(*input)++;
	return (str);
}

static char	*str_operator(char **input, int *redir)
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

static char	*str_string(char **input, bool *is_expandable)
{
	char	*str;
	char	quote;

	*is_expandable = false;
	quote = 0;
	str = ft_strdup("");
	if (!str)
		return (NULL);
	while (**input && (quote || !is_wspace(**input)))
	{
		if (!quote && (**input == '"' || **input == '\''))
			quote = *(*input)++;
		else if (quote && **input == quote)
			quote = 0, (*input)++;
		else if (!str_string_append(input, &str, is_expandable))
			return (NULL);
	}
	return (str);
}

static char	*handle_token(char **input, int *operator, bool *is_expandable)
{
	char	quote;
	char	*str;

	if (**input == '\'' || **input == '\"')
	{
		quote = **input;
		(*input)++;
		str = str_quote(input, quote, is_expandable);
	}
	else if (is_operator(**input))
		str = str_operator(input, operator);
	else
		str = str_string(input, is_expandable);
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
	bool	is_expandable;

	while (*input)
	{
		is_expandable = false;
		operator = 0;
		if (is_wspace(*input))
			input++;
		else
		{
			str = handle_token(&input, &operator, &is_expandable);
			append_token(tokens, str, operator, is_expandable);
			free(str);
		}
	}
}
