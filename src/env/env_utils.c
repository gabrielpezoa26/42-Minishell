/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:29:09 by dteruya           #+#    #+#             */
/*   Updated: 2025/06/23 17:02:57 by gcesar-n         ###   ########.fr       */
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

bool	char_expandable(char c)
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

static size_t	count_env_nodes(t_env *my_env)
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

/*
** Converts a t_env linked list to a null-terminated array of strings (char **).
** This format is required for execve.
*/
char	**env_list_to_array(t_env *my_env)
{
	char	**env_array;
	size_t	count;
	int		i;

	count = count_env_nodes(my_env);
	env_array = ft_calloc(count + 1, sizeof(char *));
	if (!env_array)
		return (NULL);
	i = 0;
	while (my_env)
	{
		env_array[i] = ft_strdup(my_env->str);
		if (!env_array[i])
		{
			mango_free(env_array);
			return (NULL);
		}
		my_env = my_env->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
