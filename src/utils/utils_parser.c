/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:03:00 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/08 11:33:56 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	verify_space(char *str)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			return (true);
		i++;
	}
	return (false);
}

char	*trim_space(char *string)
{
	int		i;
	int		j;
	char	*trimmed;

	i = 0;
	j = 0;
	trimmed = ft_malloc(trimmed);
	while (string[i] != '\0')
	{
		if ((string[i] >= 9 && string[i] <= 13) || string[i] == 32)
		{
			trimmed[j] = string[i];
			i++;
			j++;
		}
		i++;
	}
	return (trimmed);
}

char	*ft_malloc(const char *src)
{
	char	*result;

	if (!src)
		return (NULL);
	result = malloc(ft_strlen(src) + 1);
	if (!result)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	ft_strcpy(result, src);
	return (result);
}

void	*ft_calloc(size_t item_count, size_t size_bytes)
{
	void	*ptr;

	ptr = malloc(item_count * size_bytes);
	if (!ptr)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	ft_memset(ptr, 0, item_count * size_bytes);
	return (ptr);
}
