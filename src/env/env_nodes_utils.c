/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_nodes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:52:26 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/07/03 12:12:18 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			free_matrix(env_array);
			return (NULL);
		}
		my_env = my_env->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

bool	is_valid_assignment(char *str)
{
	int	i;

	if (!str || !(ft_isalpha(str[0]) || str[0] == '_'))
		return (false);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (false);
		i++;
	}
	return (str[i] == '=');
}
