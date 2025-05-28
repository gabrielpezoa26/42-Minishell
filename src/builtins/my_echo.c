/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:01:59 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/27 22:36:24 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	-> printar os char
	-> aspas simples e duplas
	-> tem a flag -n que tira o \n
	-> add_history()
	-> tratar casos de varios 'n', ex: echo hello -nnnnnn
	-> tratar caso de vazio, ex: echo ""
*/

void	my_echo(t_data *data)
{
	int	i;

	i = 0;
	if (data->input[i])
		printf("DEBUG: deu bom\n");
}
