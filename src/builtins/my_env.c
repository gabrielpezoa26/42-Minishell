/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 22:25:44 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/03 14:14:25 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
ja printa a lista, falta implementar a parte de setar, ex: VARIABLE=abcd
*/

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
