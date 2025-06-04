/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:16:56 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/04 15:30:05 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// a gnt n ta usando
bool	init_data(t_data *data)
{
	data->envp = NULL;
	data->locals = NULL;
	data->token = NULL;
	data->input = NULL;
	return (true);
}
