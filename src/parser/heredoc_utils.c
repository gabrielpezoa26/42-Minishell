/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:46:41 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/07/01 19:02:06 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	expand_var_heredoc(char *value, char **line, int *i, int index)
{
	int		size;
	int		add;
	char	*new;
	char	*old;

	old = *line;
	add = ft_strlen(value);
	size = index + add + ft_strlen(old + *i);
	new = ft_calloc(size + 1, sizeof(char));
	if (!new)
		return ;
	ft_memcpy(new, old, index);
	ft_memcpy(new + index, value, add);
	ft_memcpy(new + index + add, old + *i, ft_strlen(old + *i));
	free(*line);
	*line = new;
	*i = index + add;
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

static void	expand_hdoc_line(char **line, int *i, t_env *my_env, int found)
{
	char	*var;
	char	*val;
	int		start;
	int		len;

	(*i)++;
	start = *i;
	while (ft_isalnum((*line)[*i]) || (*line)[*i] == '_')
		(*i)++;
	len = *i - start;
	var = ft_substr(*line, start, len);
	val = my_getenv_heredoc(var, my_env);
	free(var);
	if (!val)
		val = "";
	expand_var_heredoc(val, line, i, found);
}

void	search_dollar_heredoc(char **line, t_env *my_env)
{
	int		i;
	int		index;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$')
		{
			index = i;
			expand_hdoc_line(line, &i, my_env, index);
		}
		i++;
	}
}

void	handle_heredocs(t_token **tokens, t_env *my_env)
{
	t_token	*current;

	current = *tokens;
	while (current)
	{
		if (current->type == REDIR_DELIMITER)
			process_heredoc_token(current, my_env);
		current = current->next;
	}
}
