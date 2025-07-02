/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:37:22 by dteruya           #+#    #+#             */
/*   Updated: 2025/07/01 21:43:13 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	expand_var(char *value, t_token *token, int *i)
{
	int		size;
	int		add;
	char	*new;
	char	*old;

	old = token->str;
	add = ft_strlen(value);
	size = token->index + add + ft_strlen(old + *i);
	new = ft_calloc(size + 1, sizeof(char));
	if (!new)
		return ;
	ft_memcpy(new, old, token->index);
	ft_memcpy(new + token->index, value, add);
	ft_memcpy(new + token->index + add, old + *i, ft_strlen(old + *i));
	free(token->str);
	token->str = new;
	*i = token->index + add;
}

char	*my_getenv(char *name, t_env *env, t_env *locals)
{
	size_t	len;

	len = ft_strlen(name);
	while (env)
	{
		if (!ft_strncmp(env->str, name, len) && env->str[len] == '=')
			return (env->str + len + 1);
		env = env->next;
	}
	while (locals)
	{
		if (!ft_strncmp(locals->str, name, len) && locals->str[len] == '=')
			return (locals->str + len + 1);
		locals = locals->next;
	}
	return (NULL);
}

static void	search_and_replace(t_data *data, t_token *tok, int *i)
{
	char	*var;
	char	*val;
	int		start;
	int		len;

	tok->index = *i;
	(*i)++;
	if (tok->str[*i] == '?')
	{
		(*i)++;
		val = ft_itoa(data->last_exit_status);
		expand_var(val, tok, i);
		free(val);
		return ;
	}
	start = *i;
	while (ft_isalnum(tok->str[*i]) || tok->str[*i] == '_')
		(*i)++;
	len = *i - start;
	var = ft_substr(tok->str, start, len);
	val = my_getenv(var, data->env, data->locals);
	free(var);
	if (!val)
		val = "";
	expand_var(val, tok, i);
}

static void	process_token(t_data *data, t_token **tokens, t_token *cur)
{
	int	i;

	i = 0;
	while (cur->str && cur->str[i])
	{
		if (cur->str[i] == '$')
		{
			search_and_replace(data, cur, &i);
			if (ft_strcmp(cur->str, "") == 0)
			{
				del_node(tokens, cur, free);
				break ;
			}
		}
		else
			i++;
	}
}

void	search_dollar(t_data *data, t_token **tokens)
{
	t_token	*cur;
	t_token	*temp_next_node;

	cur = *tokens;
	while (cur)
	{
		temp_next_node = cur->next;
		if (cur->is_expandable)
			process_token(data, tokens, cur);
		cur = temp_next_node;
	}
}
