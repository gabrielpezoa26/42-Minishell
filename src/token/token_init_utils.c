/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:04:55 by dteruya           #+#    #+#             */
/*   Updated: 2025/06/10 14:04:01 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	str_string_append(char **input, char **str, bool *is_exp, char quote)
{
	char	*tmp;

	if (**input == '$' && *(*input + 1) && char_expandable(*(*input + 1)) && quote == '\"')
		*is_exp = true;
	tmp = ft_join(*str, **input);
	if (!tmp)
		return (false);
	free(*str);
	*str = tmp;
	(*input)++;
	return (true);
}

char	*handle_EOF(char **input, char quote, bool *is_expandable, int *flag)
{
	char	*str;
	char	*temp;

	str = ft_strdup("");
	while (**input && (**input != quote || !is_wspace(**input)))
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
