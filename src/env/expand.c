/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:21:43 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/12 18:48:57 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*strappend(char *s1, const char *s2)
{
	char	*new_str;

	if (!s2)
		return (s1);
	if (!s1)
		return (ft_strdup(s2));
	new_str = ft_strjoin(s1, s2);
	free(s1);
	return (new_str);
}

static char	*get_var_name(char **str_ptr)
{
	char	*start;
	int		len;

	(*str_ptr)++;
	start = *str_ptr;
	if (**str_ptr == '?')
	{
		(*str_ptr)++;
		return (ft_strdup("?"));
	}
	while (ft_isalnum(**str_ptr) || **str_ptr == '_')
		(*str_ptr)++;
	len = *str_ptr - start;
	return (ft_substr(start, 0, len));
}

char	*expand_string(const char *input, t_data *data)
{
	char	*result;
	char	*var_name;
	char	*var_value;
	char	temp_char[2];

	result = ft_strdup("");
	temp_char[1] = '\0';
	while (*input)
	{
		if (*input == '$' && (ft_isalnum(*(input + 1)) || *(input + 1) == '_'))
		{
			var_name = get_var_name((char **)&input);
			var_value = my_getenv(var_name, data->env, data->locals);
			result = strappend(result, var_value);
			free(var_name);
		}
		else
		{
			temp_char[0] = *input;
			result = strappend(result, temp_char);
			input++;
		}
	}
	return (result);
}
