/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:04:55 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/29 17:05:32 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	str_string_append(char **input, char **str, bool *is_expandable)
{
	char	*tmp;

	if (**input == '$' && *(*input + 1) && char_expandable(*(*input + 1)))
		*is_expandable = true;
	tmp = ft_join(*str, **input);
	if (!tmp)
		return (false);
	free(*str);
	*str = tmp;
	(*input)++;
	return (true);
}
