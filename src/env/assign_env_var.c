/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:12:57 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/03 20:57:34 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_valid_assignment(char *string)
{
	int	i;

	if (!string || !(ft_isalpha(string[0]) || string[0] == '_'))
		return (false);
	i = 1;
	while (string[i] && string[i] != '=')
	{
		if (!(ft_isalnum(string[i]) || string[i] == '_'))
			return (false);
		i++;
	}
	if (string[i] != '=')
		return (false);
	return (true);
}

static char	*get_assignment_name(char *string)
{
	int		i;
	int		pos;
	char	*result;

	i = 0;
	pos = 0;
	while (string[pos] != '=')
		pos++;
	if (pos == 0)
		return (NULL);
	result = malloc(pos * sizeof(char));
	if (!result)
		return (NULL);
	while (i < pos)
	{
		result[i] = string[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static bool	already_exists(t_env *env, char *name)
{
	env = env->str;
	while (env)
	{
		if (ft_strncmp(env->str, name, ft_strlen(name)) == 0)
		// {
			// verifica se o prox eh '=', se for, retorna true
		// }
		env = env->next;
	}
	return (false);
}

void assign_variable(t_env **env, char *assignment)
{
	
}

bool	update_env(t_env **env, char *assignment)
{
	if (!is_valid_assignment)
		return (false);
	return (true);
}
