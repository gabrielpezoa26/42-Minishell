/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:01:59 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/28 12:52:16 by gcesar-n         ###   ########.fr       */
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

static bool remove_newline(t_data *data)
{
	bool	flag;

	flag = false;
	if (ft_strcmp(&data->input[1], "-n") == 0)
		flag = true;
	return (flag);
}

bool	my_echo(t_data *data)
{
	int	i;

	i = 0;
	if (!data->input[i])
	{
		printf("DEBUG: echo error\n");
		return (false);
	}
	while(data->input[i])
	{
		write(1, &data->input[i], 1);
		i++;
	}
	if (!remove_newline(data))
		write(1, "\n", 1);
	return (true);
}
