/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:51:29 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/02 22:03:35 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	my_pwd(void)
{
	char	*result;

	result = getcwd(NULL, 0);
	if (result == NULL)
	{
		perror("getcwd");
		return (false);
	}
	printf("%s\n", result);
	free(result);
	return (true);
}
