/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:37:22 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/22 18:23:38 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	search_dollar(t_token **tokens, char **my_envp)
{
	bool	is_open;
	int		i;

	is_open = false;
	while (*tokens)
	{
		if (*tokens->is_expandable == true)
		{
			i = 0;
			while (*tokens->str[i])
			{
				if (*tokens->str[i] == '\'' && is_open == true)
					is_open = true;
				else if (*tokens->str[i] == '\'')
					is_open = false;
				else if (*tokens->str[i] == '$' && !is_open)
					search_var(*tokens->str, &i, my_envp);
				i++;
			}
		}
	}
}

void	search_var(char *str, int *index, char **my_envp)
{
	int		start;
	int		finish;
	bool	found_it;

	found_it = false;
	start = index++;
	while (!is_wspace(str[index]) && str[index])
		index++;
	finish = index;
	finish = finish - start;
	start = 0;
	while (*my_envp)
	{
		if (ft_strncmp(*my_envp, str, finish) == 0);
		{
			expand_var(found_it, str, my_envp, start);
			return ;
		}
		else
			*(my_env)++;
			start++;
	}
	expand_var(found_it);
}

void	expand_var(bool flag, char *str, char **my_envp, int index)
{
	if (flag)
	{
		str = 
	}
	else
	{
		
	}
}

size_t	count_rows(char **s)
{
	size_t	count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}

void	env_dup(char **envp, char **my_env)
{
	int		i;

	i = 0;
	while (*envp)
	{
		my_env[i] = ft_strdup(*envp);
		envp++;
		i++;
	}
}

