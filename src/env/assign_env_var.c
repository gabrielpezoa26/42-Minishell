/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:12:57 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/30 12:46:52 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*str_suport(char *input)
{
	char	*str;
	char	*temp;
	char	quote;

	quote = *input;
	str = ft_strdup("");
	input++;
	while (*input && *input != quote)
	{
		temp = ft_join(str, *input);
		if (!temp)
			return (NULL);
		free(str);
		str = temp;
		input++;
	}
	if (*input == quote)
		input++;
	return (str);
}

char	*get_assignment_name(char *str)
{
	int		len;
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

bool	update_value(t_env **list, char *name, char *assignment)
{
	t_env	*curr;

	curr = *list;
	while (curr)
	{
		if (ft_strncmp(curr->str, name, ft_strlen(name)) == 0
			&& curr->str[ft_strlen(name)] == '=')
		{
			free(curr->str);
			if (is_quote(assignment[0]))
				curr->str = str_suport(assignment);
			else
				curr->str = ft_strdup(assignment);
			return (true);
		}
		curr = curr->next;
	}
	return (false);
}

static void	assign_variable(t_env **list, char *assignment)
{
	char	*name;

	if (!is_valid_assignment(assignment))
		return ;
	name = get_assignment_name(assignment);
	if (!name)
		return ;
	if (!update_value(list, name, assignment))
		append_env(list, assignment);
	free(name);
}

void	handle_assignments(t_token *tokens, t_env **env)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		if (is_valid_assignment(curr->str))
			assign_variable(env, curr->str);
		curr = curr->next;
	}
}
