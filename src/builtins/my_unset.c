/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:41:05 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/23 17:41:17 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_valid_unset_identifier(const char *str)
{
	int	i;

	if (!str || !(ft_isalpha(str[0]) || str[0] == '_'))
		return (false);
	i = 1;
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (false);
		i++;
	}
	return (true);
}

static void	remove_var(t_env **list, const char *name)
{
	t_env	*current;
	t_env	*prev;
	size_t	len;

	if (!list || !*list || !name)
		return ;
	len = ft_strlen(name);
	current = *list;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(current->str, name, len) == 0
			&& (current->str[len] == '=' || current->str[len] == '\0'))
		{
			if (prev)
				prev->next = current->next;
			else
				*list = current->next;
			free(current->str);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	my_unset(char **args, t_data *data)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (args[i])
	{
		if (!is_valid_unset_identifier(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1;
		}
		else
		{
			remove_var(&data->env, args[i]);
			remove_var(&data->locals, args[i]);
		}
		i++;
	}
	return (status);
}
