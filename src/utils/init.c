/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:16:56 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/05 17:53:43 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void init_shell(t_mango *mango)
// {
// }

// static void init_directory(t_mango *mango)
// {
// }

bool	init_data(t_mango *mango)
{
	mango->envp = NULL;
	mango->token = NULL;
	mango->input = NULL;
	return (true);
}
