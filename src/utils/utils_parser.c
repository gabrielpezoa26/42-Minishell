/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:03:00 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/12 21:30:16 by gcesar-n         ###   ########.fr       */
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
			i++;
		else
			return (false);
	}
	return (true);
}

char	*trim_space(char *string)
{
	int		i;
	int		j;
	char	*trimmed;

	trimmed = ft_malloc(ft_strlen(string) + 1);
	if (!trimmed)
		return (NULL);
	i = 0;
	j = 0;
	while (string[i] != '\0')
	{
		if (!((string[i] >= 9 && string[i] <= 13) || string[i] == 32))
			trimmed[j++] = string[i];
		i++;
	}
	trimmed[j] = '\0';
	return (trimmed);
}

void	*ft_malloc(size_t size)
{
	void	*result;

	result = malloc(size);
	if (!result)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
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
