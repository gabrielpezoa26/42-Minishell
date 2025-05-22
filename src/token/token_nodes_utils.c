/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_nodes_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:12:58 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/22 11:26:05 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	word_count(char *s)
{
	int	num;
	int	word;

	num = 0;
	word = 0;
	while (*s)
	{
		if ((!is_wspace(*s) || *s == '$') && word == 0)
		{
			word = 1;
			num++;
		}
		else if (is_wspace(*s) || *s == '$')
			word = 0;
		s++;
	}
	return (num);
}

void	find_dollar_sign(int v[], char *str, int size)
{
	int	i;

	i = 0;
	while (i < size && *str)
	{
		if (!is_wspace(*str))
		{
			if (*str == '$')
				v[i] = 1;
			else
				v[i] = 0;
			i++;
			while (*str && !is_wspace(*str) && *str != '$')
				str++;
		}
		else
			str++;
	}
}

void	free_tokens(t_token **tokens)
{
	t_token	*next_token;

	if (tokens == NULL)
		return ;
	while (*tokens)
	{
		next_token = (*tokens)->next;
		free((*tokens)->str);
		free((*tokens)->array);
		free(*tokens);
		*tokens = next_token;
	}
	*tokens = NULL;
}
