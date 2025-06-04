/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:12:57 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/04 13:45:22 by gcesar-n         ###   ########.fr       */
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
	result = malloc((pos + 1) * sizeof(char));
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
	while (env != NULL)
	{
		if ((ft_strncmp(env->str, name, ft_strlen(name)) == 0)
				&& (env->str[ft_strlen(name)] == '='))
			return (true);
		env = env->next;
	}
	return (false);
}

static void	assign_variable(t_env **env, char *assignment)
{
	char	*name;

	name = get_assignment_name(assignment);
	if (!name)
		return ;
	if (!update_env(env, assignment))
		append_env(env, assignment);
	free(name);
}

static bool	update_env_value(t_env **env, char *name, char *assignment)
{
	t_env	*curr;

	curr = *env;
	while (curr)
	{
		if (ft_strncmp(curr->str, name, ft_strlen(name)) == 0
			&& curr->str[ft_strlen(name)] == '=')
		{
			free(curr->str);
			curr->str = ft_strdup(assignment);
			return (true);
		}
		curr = curr->next;
	}
	return (false);
}

bool	update_env(t_env **env, char *assignment)
{
	char	*name;
	bool	result;

	if (!is_valid_assignment(assignment))
		return (false);
	name = get_assignment_name(assignment);
	if (!name || !already_exists(*env, name))
	{
		free(name);
		return (false);
	}
	result = update_env_value(env, name, assignment);
	free(name);
	return (result);
}

void	handle_assignments(t_token *tokens, t_env **env)
{
	t_token *tmp;
	
	tmp = tokens;
	while (tmp)
	{
		if (is_valid_assignment(tmp->str))
			assign_variable(env, tmp->str);
		tmp = tmp->next;
	}
}
