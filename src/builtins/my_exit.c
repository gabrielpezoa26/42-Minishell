/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 22:23:33 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/23 16:10:51 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	is_numeric(const char *str)
{
	if (!str)
		return (false);
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (false);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

static int	arg_count(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

static void	handle_non_numeric(t_data *data, char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit_minishell(data, 255);
}

int	my_exit(char **args, t_data *data)
{
	int	count;
	int	exit_code;

	ft_putendl_fd("exit", 1);
	count = arg_count(args);
	if (count == 1)
	{
		exit_code = data->last_exit_status;
		exit_minishell(data, exit_code);
	}
	if (!is_numeric(args[1]))
		handle_non_numeric(data, args[1]);
	if (count > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	exit_code = ft_atoi(args[1]);
	exit_minishell(data, exit_code % 256);
	return (0);
}
