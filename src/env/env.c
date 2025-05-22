/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:37:22 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/22 16:20:25 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_variables(t_token **tokens)
{
	while (*tokens)
	{
		if ()
	}
}

size_t	count_rows(char **s)
{
	size_t	count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}

void	env_dup(char **envp, char **my_env)
{
	int		i;

	i = 0;
	while (*envp)
	{
		my_env[i] = ft_strdup(*envp);
		envp++;
		i++;
	}
}

