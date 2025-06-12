/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:46:41 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/12 16:12:54 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	expand_var_heredoc(char *value, char *line, int *i)
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

char	*my_getenv_heredoc(char *name, t_env *env)
{
	size_t	len;

	len = ft_strlen(name);
	while (env)
	{
		if (!ft_strncmp(env->str, name, len) && env->str[len] == '=')
			return (env->str + len + 1);
		env = env->next;
	}
	return (NULL);
}

static void	search_and_replace_heredoc(char *line, int *i, t_env *my_env)
{
	char	*var;
	char	*val;
	int		start;
	int		len;

	(*i)++;
	start = *i;
	while (ft_isalnum(line[*i]) || line[*i] == '_')
		(*i)++;
	len = *i - start;
	var = ft_substr(line, start, len);
	val = my_getenv_heredoc(var, my_env);
	free(var);
	if (!val)
		val = "";
	expand_var_heredoc(val, tok, i);
}

void	search_dollar_heredoc(char *line, t_env *my_env)
{
	int		i;
	
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			search_and_replace_heredoc(line, &i, my_env);
		i++;
	}
}

