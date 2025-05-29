/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:37:22 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/29 17:54:36 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	expand_var(char *value, t_token *token, int *i)
{
	int		size;
	int		amount;
	char	*new_str;
	char	*old_str;

	old_str = token->str;
	size = 0;
	amount = 0;
	if ((size_t)(*i) > ft_strlen(old_str))
		return ;
	while (size <= token->index)
		size++;
	amount = ft_strlen(value);
	size = amount + size;
	size += ft_strlen(token->str + *i);
	new_str = ft_calloc(size + 1, sizeof(char));
	ft_memcpy(new_str, old_str, token->index);
	ft_memcpy(new_str + token->index, value, ft_strlen(value));
	ft_memcpy(new_str + token->index + ft_strlen(value),
		old_str + *i, ft_strlen(old_str + *i));
	new_str[size] = '\0';
	free(token->str);
	token->str = new_str;
	*i = token->index + ft_strlen(value);
}

static char	*my_getenv(char *name, char **my_envp)
{
	size_t	len;
	int		i;

	len = (size_t)ft_strlen(name);
	i = 0;
	while (my_envp[i] != NULL)
	{
		if ((ft_strncmp(my_envp[i], name, len) == 0)
			&& (my_envp[i][len] == '='))
			return (&my_envp[i][len + 1]);
		i++;
	}
	return (NULL);
}

static void	search_and_replace_rs(t_token *token, int *i, char **my_envp)
{
	char	*variable;
	char	*value;
	int		len;
	int		start;

	token->index = *i;
	(*i)++;
	start = *i;
	while (ft_isalnum((*token).str[*i]) || (*token).str[*i] == '_')
	{
		(*i)++;
	}
	len = *i - start;
	variable = ft_substr(token->str, start, len);
	value = my_getenv(variable, my_envp);
	free(variable);
	if (!value)
	{
		expand_var("", token, i);
		return ;
	}
	expand_var(value, token, i);
}

void	search_dollar(t_data *data, t_token **tokens)
{
	t_token	*curr;
	int		i;

	curr = *tokens;
	while (curr)
	{
		if (curr->is_expandable == true)
		{
			i = 0;
			while (curr->str[i])
			{
				if (curr->str[i] == '$')
				{
					search_and_replace_rs(curr, &i, data);
					i = 0;
				}
				else
					i++;
			}
		}
		curr = curr->next;
	}
}
