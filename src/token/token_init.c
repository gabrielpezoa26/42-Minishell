/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:19:56 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/19 16:15:26 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*str_quote(char **input, char quote, bool *is_expandable)
{
	char	*str;
	char	*temp;

	str = ft_strdup("");
	while (**input != quote)
	{
		if (quote == '\"' && **input == '$')
			*is_expandable = true;
		temp = ft_join(str, **input);
		free(str);
		str = temp;
		(*input)++;
	}
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
	char	*temp;

	str = ft_strdup("");
	while (**input && !is_wspace(**input))
	{
		if (**input == '$')
			*is_expandable = true;
		temp = ft_join(str, **input);
		free(str);
		str = temp;
		(*input)++;
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
			append_node(tokens, str, operator);
			free(str);
		}
	}
}
