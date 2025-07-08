/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:02:25 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/07/08 18:59:01 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_swap_str(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sort_env_array(char **array, size_t count)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(array[i], array[j]) > 0)
				ft_swap_str(&array[i], &array[j]);
			j++;
		}
		i++;
	}
}

char	**create_env_array(t_env *env, size_t *count)
{
	t_env	*curr;
	char	**array;
	size_t	i;

	*count = 0;
	curr = env;
	while (curr && ++(*count))
		curr = curr->next;
	if (*count == 0)
		return (NULL);
	array = ft_calloc(*count + 1, sizeof(char *));
	if (!array)
		return (NULL);
	curr = env;
	i = 0;
	while (curr)
	{
		array[i++] = curr->str;
		curr = curr->next;
	}
	return (array);
}

void	print_sorted_env(t_env *env)
{
	char	**array;
	size_t	count;
	size_t	i;
	size_t	j;

	array = create_env_array(env, &count);
	if (!array)
		return ;
	sort_env_array(array, count);
	i = 0;
	while (i < count)
	{
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (array[i][j] != '\0')
		{
			if (array[i][j - 1] == '=')
				ft_putchar_fd('\"', 1);
			ft_putchar_fd(array[i][j], 1);
			j++;
		}
		ft_putstr_fd("\"\n", 1);
		i++;
	}
	free(array);
}

t_env	*find_node(t_env *list, const char *name)
{
	t_env	*curr;
	size_t	len;

	curr = list;
	if (!list || !name)
		return (NULL);
	len = ft_strlen(name);
	while (curr)
	{
		if (ft_strncmp(curr->str, name, len) == 0
			&& (curr->str[len] == '=' || curr->str[len] == '\0'))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}
