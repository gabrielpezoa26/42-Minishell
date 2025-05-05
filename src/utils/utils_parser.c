/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:03:00 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/05 14:20:22 by gcesar-n         ###   ########.fr       */
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
