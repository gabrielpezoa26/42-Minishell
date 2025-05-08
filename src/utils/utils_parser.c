/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:03:00 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/07 22:54:40 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	verify_space(char *str)
{
	int	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			return (true);
		i++;
	}
	return (false);
}
/*
	falta implementar o strcpy
*/

// char	*ft_malloc(char *to_malloc)
// {
// 	char	*maloka;

// 	if (!to_malloc)
// 		return (NULL);
// 	maloka = malloc(ft_strlen(to_malloc) + 1);
// 	if (!maloka)
// 	{
// 		printf("malloc failed\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	ft_strcpy(maloka, to_malloc);
// 	return (maloka);
// }
