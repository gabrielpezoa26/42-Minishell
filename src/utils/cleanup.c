/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:16:51 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/15 18:34:53 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_structs(t_data *target)
{
	if (target)
		free(target);
}

/**
 * exit_minishell - free's the structs and call's exit(1)
 * 
 * @data: pointer to the main struct
 * @message: message to be printed
 * 
 * @return: void
 */
void	exit_minishell(t_data *data, char *message)
{
	free_structs(data);
	printf("%s\n", message);
	exit(1);
}
