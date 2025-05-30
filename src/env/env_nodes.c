/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:21:25 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/30 15:21:39 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env	*init_env(char	*content)
{
	t_env	*new_env;

	new_env = (t_env *)ft_malloc(sizeof(t_env), sizeof(char));
	new_env->str = ft_strdup(content);
	new_env->next = NULL;
	return (new_env);
}

void	append_env(t_env **my_env, char *content)
{
	t_env	*env;

	env = init_env(content);
	if (*my_env == NULL)
		*my_env = env;
	else
		add_back_env(my_env, env);
}

/**
 * t_env *last_node -> finds the last node from the list and returns it
 *
 * @token: the token at the top of the list
 * 
 * @return: returns the last token
 */
t_env	*last_env(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}

/**
 * void add_back -> adds the given token at the end of the list
 *
 * @tokens: the list of the tokens
 * @node: the token to be added
 * 
 * @return: void
 */
void	add_back_env(t_env **my_env, t_env *node)
{
	t_env	*last;

	if (my_env == NULL || node == NULL)
		return ;
	if (*my_env == NULL)
	{
		*my_env = node;
		return ;
	}
	last = last_env(*my_env);
	last->next = node;
}