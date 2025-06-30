/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:59:53 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/29 18:05:16 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static bool	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !(ft_isalpha(str[0]) || str[0] == '_' || is_quote(str[0])))
		return (false);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (false);
		i++;
	}
	return (true);
}

static void	handle_export_arg(char *arg, t_data *data, int *status)
{
	char	*name;
	t_env	*node;

	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		*status = 1;
		return ;
	}
	name = get_assignment_name(arg);
	node = find_node(data->locals, name);
	if (node)
		remove_var(&data->locals, name);
	if (!update_value(&data->env, name, arg))
		append_env(&data->env, arg);
	free(name);
}

int	my_export(char **args, t_data *data)
{
	int	i;
	int	status;

	status = 0;
	if (!args[1])
	{
		print_sorted_env(data->env);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		handle_export_arg(args[i], data, &status);
		i++;
	}
	return (status);
}
