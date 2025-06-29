/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:19:56 by dteruya           #+#    #+#             */
/*   Updated: 2025/06/29 17:49:40 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*banana(char *str, char **input)
{
	char	*temp;

	while (**input && **input != ' ' && !is_operator(**input))
	{
		while (**input == '\'' || **input == '\"')
			(*input)++;
		if (**input)
		{
			temp = ft_join(str, **input);
			if (!temp)
				return (NULL);
			free(str);
			str = temp;
			(*input)++;
		}
	}
	return (str);
}

static char	*str_quote(char **input, char quote, bool *is_expandable)
{
	char	*str;
	char	*temp;

	*is_expandable = false;
	str = ft_strdup("");
	(*input)++;
	while (**input && **input != quote)
	{
		if (quote == '\"' && **input == '$' && *(*input + 1)
			&& is_char_expandable(*(*input + 1)))
			*is_expandable = true;
		temp = ft_join(str, **input);
		if (!temp)
			return (NULL);
		free(str);
		str = temp;
		(*input)++;
	}
	if (**input == quote)
		(*input)++;
	if (**input != ' ')
		str = banana(str, input);
	return (str);
}

static char	*handle_heredoc_delimiter(char **input, bool *is_expandable)
{
	char	*str;
	char	quote;

	*is_expandable = true;
	quote = '\0';
	while (is_wspace(**input))
		(*input)++;
	if (**input == '\'' || **input == '\"')
	{
		quote = *(*input)++;
		*is_expandable = false;
	}
	str = ft_strdup("");
	while (**input)
	{
		if (quote == '\0' && (is_wspace(**input) || is_operator(**input)))
			break ;
		if (quote != '\0' && **input == quote)
			break ;
		if (!str_append(input, &str, is_expandable, quote))
			return (NULL);
	}
	if (quote != '\0' && **input == quote)
		(*input)++;
	return (str);
}

static char	*handle_token(char **input, int *op, bool *is_expand, int *flag)
{
	char	*str;

	if (*flag == 1)
	{
		str = handle_heredoc_delimiter(input, is_expand);
		*flag = 0;
	}
	else if (**input == '\'' || **input == '\"')
	{
		str = str_quote(input, **input, is_expand);
	}
	else if (is_operator(**input))
	{
		str = str_operator(input, op);
		if (str && ft_strcmp(str, "<<") == 0)
			*flag = 1;
	}
	else
	{
		str = str_string(input, is_expand);
	}
	return (str);
}

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
			if (str)
			{
				append_token(tokens, str, operator, is_expandable);
				free(str);
			}
		}
	}
}
