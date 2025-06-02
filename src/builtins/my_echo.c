/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:01:59 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/01 22:59:55 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	-> tratar casos de varios 'n', ex: echo -nnnn hello
	-> tratar caso de vazio, ex: echo ""
*/

static	int	arg_size(char **args)
{
	int		len;

	len = 0;
	while (args[len])
		len++;
	return (len);
}

bool	my_echo(char **arg_list)
{
	bool	remove_newline;
	int		i;

	i = 1;
	remove_newline = false;
	if (arg_size(arg_list) > 1)
	{
		while (arg_list[i] && ft_strcmp(arg_list[i], "-n") == 0)
		{
			remove_newline = true;
			i++;
		}
		while (arg_list[i])
		{
			ft_putstr_fd(arg_list[i], 1);
			if (arg_list[i + 1] && arg_list[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (remove_newline == false)
		write(1, "\n", 1);
	return (true);
}
