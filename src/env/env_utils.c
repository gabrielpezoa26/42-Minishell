/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:29:09 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/26 10:55:02 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	my_env[i] = NULL;
}

bool	char_expandable(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (true);
	return (false);
}

void	ft_strcat(char *dst, const char *src, size_t index)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!dst)
		return ;
	while (dst[i])
		i++;
	j = index;
	while (src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
}
