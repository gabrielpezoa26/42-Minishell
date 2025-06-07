/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:12:57 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/05 18:09:54 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * is_valid_assignment-> checks if it's a valid assignment (start with letters
 * 			or a '_' only)
 *
 * @str: the string to be checked
 * 
 * @return: true if valid, false otherwise
 */
bool	is_valid_assignment(char *str)
{
	int	i;

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

/**
 * get_assignment_name-> extracts the "name", from the assignment
 *
 * @str: the whole assignment, ex:  EXAMPLE=hello
 * 
 * @return: the "name" of the assignment
 */
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

/**
 * update_value-> if the "name" already exists, then replaces it with
 * 					the new added value
 * 
 * @list: the "env" linked list
 * @name: only the part before the '=' sign
 * @assignment: the whole string, ex:  EXAMPLE=hello
 * 
 * @return: true if updated, false otherwise
 */
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
			curr->str = ft_strdup(assignment);
			return (true);
		}
		curr = curr->next;
	}
	return (false);
}

/**
 * assign_variable-> assigns a variable, lol
 * 
 * @list: the "env" linked list
 * @assignment: the whole string, ex:  EXAMPLE=hello
 * 
 * @return: void
 */
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
