/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:19:56 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/15 19:31:56 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * char *str_quote - extracts what is inside quotes (either single or double)
 * 
 * @input: input from command line
 * @quote: marks if it is single or double
 * 
 * @return: a pointer to the extracted content
 */
static char	*str_quote(char *input, char quote)
{
	char	*str;
	char	*temp;

	str = ft_strdup("");
	while (*input && *input != quote)
	{
		temp = ft_join(str, *input);
		free(str);
		str = temp;
		input++;
	}
	if (*input == quote)
		input++;
	return (str);
}

/**
 * char *str_operator - identify the operator type and malloc's it
 * 
 * @input: input from command line
 * @redir: marks the type based on the enum
 * 
 * @return: a representation of the operator type
 */
static char	*str_operator(char *input, int *redir)
{
	char	*str;
	int		c;

	if (*input == '|')
		*redir = 1;
	else if (*input == '<')
		*redir = 2;
	else if (*input == '>')
		*redir = 3;
	input++;
	if (*input == '>' && *redir == 3)
	{
		*redir = 4;
		input++;
		return (ft_strdup(">>"));
	}
	else if (*input == '<' && *redir == 2)
	{
		*redir = 5;
		input++;
		return (ft_strdup("<<"));
	}
	c = *(input - 1);
	str = ft_strdup_char(&c);
	return (str);
}

/*
	criar um node dentro da init token
	seta toda a struct com as var do if else
	ja passa pro append node com o no pronto

	BOOM_IS_? = false;
*/

/**
 * char *handle_token - extracts the token from the input
 * 
 * @input: input from command line
 * @operator: the operator type to be identified
 * 
 * @return:a pointer to the extracted tokens
 */
static char	*handle_token(char **input, int *operator)
{
	char	quote;
	char	*str;
	int		i;

	*operator = 0;
	while (**input == ' ' || **input == '\t')
		(*input)++;
	if (**input == '\'' || **input == '\"')
	{
		quote = *(*input)++;
		str = str_quote(*input, quote);
		i = 0;
		while ((*input)[i] && (*input)[i] != quote)
			i++;
		if ((*input)[i] == quote)
			i++;
		*input += i;
		return (str);
	}
	if (is_operator(**input))
	{
		str = str_operator(*input, operator);
		*input += ft_strlen(str);
		return (str);
	}
	while (**input && **input != ' ' && !is_operator(**input))
		(*input)++;
	return (NULL);
}

/**
 * void init_tokens - extracts each token initialize them, and
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

	while (*input)
	{
		str = handle_token(&input, &operator);
		if (str)
			append_node(tokens, str, operator);
	}
}
