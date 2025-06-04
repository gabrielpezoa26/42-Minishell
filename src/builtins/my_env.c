/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 22:25:44 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/04 13:21:39 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	my_env(t_data *data)
{
	t_env	*env;

	env = data->env;
	if (!data->env)
		return (false);
	while (env != NULL)
	{
		printf("%s\n", env->str);
		env = env->next;
	}
	return (true);
}
