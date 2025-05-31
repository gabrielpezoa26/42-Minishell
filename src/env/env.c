/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:37:22 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/31 00:09:15 by gcesar-n         ###   ########.fr       */
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

static char	*my_getenv(char *name, t_env **my_envp)
{
	t_env	*env_copy;
	size_t	len;

	len = ft_strlen(name);
	env_copy = *my_envp;
	while (env_copy != NULL)
	{
		if ((ft_strncmp(env_copy->str, name, len) == 0)
			&& (env_copy->str[len] == '='))
			return (&env_copy->str[len + 1]);
		env_copy = env_copy->next;
	}
	return (NULL);
}

static void	search_and_replace_rs(t_token *token, int *i, t_env **my_envp)
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

void	search_dollar(t_env **my_env, t_token **tokens)
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
					search_and_replace_rs(curr, &i, my_env);
					i = 0;
				}
				else
					i++;
			}
		}
		curr = curr->next;
	}
}
