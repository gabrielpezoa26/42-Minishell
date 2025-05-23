/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:37:22 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/23 15:50:39 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	expand_var(char *value, t_token *token, int *i)
{
	int		size;
	int		amount;
	int		pos;
	char	*old_str;

	size = 0;
	amount = 0;
	pos = *i;
	old_str = ft_strdup(token->str);
	while (size <= token->index)
		size++;
	while (amount < ft_strlen(value))
	{
		size++;
		amount++;
	}
	while (token->str[(*i)++])
		size++;
	free((*token).str);
	token->str = ft_malloc(size, sizeof(char));
	ft_strlcpy(token->str, old_str, token->index);
	ft_strcat(token->str, value, 0);
	ft_strcat(token->str, old_str, pos);
	*i = *i - ft_strlen(value) + ft_strlen(old_str);
	free(old_str);
}

static char *my_getenv(char *name, char **my_envp)
{
	size_t	len;
	int		i;

	len = (size_t)ft_strlen(name);
	i = 0;
	while (my_envp[i] != NULL)
	{
		if ((ft_strncmp(my_envp[i], name, len) == 0) && (my_envp[i][len] == '='))
			return (&my_envp[i][len + 1]);
		i++;
	}
	return NULL;
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
		(*i)++;
	(*i)--;
	len = *i - start;
	variable = ft_substr(token->str, start, len);
	value = my_getenv(variable, my_envp);
	free(variable);
	(*i)++;
	if (!value)
	{
		expand_var("", token, i);
		return ;
	}
	expand_var(value, token, i);
}

void	search_dollar(t_token **tokens, char **my_envp)
{
	bool	is_open;
	int		i;
	t_token	*curr;

	is_open = false;
	curr = *tokens;
	while (curr)
	{
		if (curr->is_expandable == true)
		{
			i = 0;
			while (curr->str[i])
			{
				if (curr->str[i] == '$')
					search_and_replace_rs(curr, &i, my_envp);
				i++;
			}
		}
		curr = curr->next;
	}
}
