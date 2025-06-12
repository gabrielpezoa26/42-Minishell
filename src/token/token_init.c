/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:19:56 by dteruya           #+#    #+#             */
/*   Updated: 2025/06/12 19:21:32 by gcesar-n         ###   ########.fr       */
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

	quote = '\0';
	str = ft_strdup("");
	if (!str)
		return (NULL);
	while (**input && (quote || !is_wspace(**input)))
	{
		if (!quote && (**input == '\"' || **input == '\''))
			quote = *(*input)++;
		else if (quote && **input == quote)
		{
			quote = '\0';
			(*input)++;
		}
		else
		{
			if ((quote == '\0' || quote == '\"') && **input == '$' && *(*input + 1))
				*is_expandable = true;
			if (!str_append(input, &str, is_expandable, quote))
				return (NULL);
		}
	}
	return (str);
}

static char	*handle_token(char **input, int *oper, bool *is_expand, int *flag)
{
	char	quote;
	char	*str;

	quote = '\0';
	if (**input == '\'' || **input == '\"')
	{
		quote = **input;
		(*input)++;
		if (*flag == 0)
			str = str_quote(input, quote, is_expand);
		else
			str = handle_eof(input, quote, is_expand, flag);
	}
	else if (is_operator(**input))
	{
		str = str_operator(input, oper);
		if (ft_strcmp(str, "<<") == 0)
			*flag = 1;
	}
	else
		if (*flag == 0)
			str = str_string(input, is_expand);
		else
			str = handle_eof(input, quote, is_expand, flag);
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
	int		flag;
	bool	is_expandable;

	flag = 0;
	while (*input)
	{
		is_expandable = false;
		operator = 0;
		if (is_wspace(*input))
			input++;
		else
		{
			str = handle_token(&input, &operator, &is_expandable, &flag);
			append_token(tokens, str, operator, is_expandable);
			free(str);
		}
	}
}
