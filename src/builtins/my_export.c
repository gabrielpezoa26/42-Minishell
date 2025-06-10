/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:59:53 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/10 19:45:47 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	var_already_exists(t_env *env, char *name)
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

bool	my_export(t_env *my_env, char *args)
{
	char	*name;

	name = get_assignment_name(args);
	if (!name || !is_valid_assignment(args))
		return (false);
	if (var_already_exists(my_env, name))
		update_value(&my_env, name, args);
	else if (!var_already_exists(my_env, name))
		append_env(&my_env, args);
	if (name)
		free(name);
	return (true);
}
