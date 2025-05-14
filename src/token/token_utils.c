/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:18:57 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/14 18:12:18 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_operator(char input)
{
	if (input == '|' || input == '>' || input == '<')
		return (true);
	return (false);
}

char	*ft_join(const char *s1, char s2)
{
	size_t	size;
	size_t	i;
	char	*dest_ptr;

	if (s1 == NULL || s2 == '\0')
		return (NULL);
	size = ft_strlen(s1) + 2;
	dest_ptr = malloc(size);
	if (dest_ptr == NULL)
		return (NULL);
	i = 0;
	while (*s1 != '\0')
	{
		dest_ptr[i] = *s1;
		i++;
		s1++;
	}
	dest_ptr[i] = s2;
	i++;
	dest_ptr[i] = '\0';
	return (dest_ptr);
}

char	*ft_strdup_char(int index)
{
	char	*dest;
	char	*token;

	token = "|<>";
	dest = (char *)malloc(2 * sizeof(char));
	if (dest == NULL)
		return (NULL);
	dest[0] = token[index - 1];
	dest[1] = '\0';
	return (dest);
}
