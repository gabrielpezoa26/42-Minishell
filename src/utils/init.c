/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:16:56 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/08 10:05:25 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	init_data(t_data *data)
{
	data->envp = NULL;
	data->token = NULL;
	data->input = NULL;
	return (true);
}

// bool	init_token(t_token *token)
// {
// }