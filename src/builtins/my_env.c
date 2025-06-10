/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 22:25:44 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/10 19:47:30 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	my_environ(t_env *my_env)
{
	if (!my_env)
		return (false);
	while (my_env != NULL)
	{
		printf("%s\n", my_env->str);
		my_env = my_env->next;
	}
	return (true);
}
