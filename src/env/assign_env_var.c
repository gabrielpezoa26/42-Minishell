/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:12:57 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/04 14:58:59 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_valid_assignment(char *str)
{
	int i;

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

static char	*get_assignment_name(char *str)
{
	int	len;
	char	*name;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	if (len == 0)
		return (NULL);
	name = malloc((len + 1) * sizeof(char));
	if (!name)
		return (NULL);
	ft_memcpy(name, str, len);
	name[len] = '\0';
	return (name);
}

static bool	update_value(t_env **lst, char *name, char *assignment)
{
	t_env *cur = *lst;
	while (cur)
	{
		if (ft_strncmp(cur->str, name, ft_strlen(name)) == 0
			&& cur->str[ft_strlen(name)] == '=')
		{
			free(cur->str);
			cur->str = ft_strdup(assignment);
			return (true);
		}
		cur = cur->next;
	}
	return (false);
}

static void	assign_variable(t_env **list, char *assignment)
{
	char *name;

	if (!is_valid_assignment(assignment))
		return ;
	name = get_assignment_name(assignment);
	if (!name)
		return ;
	if (!update_value(list, name, assignment))
		append_env(list, assignment);
	free(name);
}

void	handle_assignments(t_token *tokens, t_env **locals)
{
	t_token *cur = tokens;

	while (cur)
	{
		if (is_valid_assignment(cur->str))
			assign_variable(locals, cur->str);
		cur = cur->next;
	}
}
