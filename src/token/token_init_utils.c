/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:04:55 by dteruya           #+#    #+#             */
/*   Updated: 2025/06/29 17:49:40 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	str_append(char **input, char **str, bool *is_exp, char quote)
{
	char	*tmp;

	if (**input == '$' && *(*input + 1) && is_char_expandable(*(*input + 1))
		&& quote != '\'')
	{
		*is_exp = true;
	}
	tmp = ft_join(*str, **input);
	if (!tmp)
		return (false);
	free(*str);
	*str = tmp;
	(*input)++;
	return (true);
}

char	*handle_eof(char **input, char quote, bool *is_expandable, int *flag)
{
	char	*str;
	char	*temp;
	bool	is_open;

	is_open = false;
	if (quote != '\0')
		is_open = true;
	str = ft_strdup("");
	while (**input && **input != quote && (!is_wspace(**input) || is_open))
	{
		if (!is_quote(quote))
			*is_expandable = true;
		temp = ft_join(str, **input);
		free(str);
		str = temp;
		(*input)++;
	}
	if (**input == quote)
		(*input)++;
	*flag = 0;
	return (str);
}

char	*get_double_op(char **input, int *op)
{
	if (**input == '<' && *(*input + 1) == '<')
	{
		*op = REDIR_DELIMITER;
		*input += 2;
		return (ft_strdup("<<"));
	}
	if (**input == '>' && *(*input + 1) == '>')
	{
		*op = REDIR_APPEND;
		*input += 2;
		return (ft_strdup(">>"));
	}
	return (NULL);
}

char	*str_operator(char **input, int *op)
{
	char	*str;

	str = get_double_op(input, op);
	if (str)
		return (str);
	if (**input == '<')
	{
		*op = REDIR_IN;
		(*input)++;
		return (ft_strdup("<"));
	}
	if (**input == '>')
	{
		*op = REDIR_OUT;
		(*input)++;
		return (ft_strdup(">"));
	}
	if (**input == '|')
	{
		*op = PIPE;
		(*input)++;
		return (ft_strdup("|"));
	}
	return (NULL);
}

char	*str_string(char **input, bool *is_expandable)
{
	char	*str;
	char	quote;

	quote = '\0';
	str = ft_strdup("");
	if (!str)
		return (NULL);
	while (**input && !is_wspace(**input) && !is_operator(**input))
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
			if (!str_append(input, &str, is_expandable, quote))
				return (NULL);
			if (quote != '\0')
				str = append_until_quote(input, str, quote);
		}
	}
	return (str);
}
