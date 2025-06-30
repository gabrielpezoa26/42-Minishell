/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:29:09 by dteruya           #+#    #+#             */
/*   Updated: 2025/06/30 12:47:16 by gcesar-n         ###   ########.fr       */
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

void	env_dup(char **envp, t_env **my_env)
{
	char	*temp;

	while (*envp)
	{
		temp = ft_strdup(*envp);
		append_env(my_env, temp);
		free(temp);
		envp++;
	}
}

bool	is_char_expandable(char c)
{
	if (ft_isalpha(c) || c == '_' || c == '?')
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

size_t	count_env_nodes(t_env *my_env)
{
	size_t	count;

	count = 0;
	while (my_env)
	{
		count++;
		my_env = my_env->next;
	}
	return (count);
}
