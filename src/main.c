/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:37:42 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/04/08 17:26:12 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	initialize(void)
// {
// 	while (1)
// 	{
// 		loop;
// 	}
// }

int main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	(void)argc;
	for (int i = 0; envp[i]; i++)
		printf("%s\n", envp[i]);
//	initialize();
	return (0);
}
