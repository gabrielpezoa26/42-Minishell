/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_id.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:50:51 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/27 14:50:53 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_builtin(const char *cmd_name)
{
	if (!cmd_name)
		return (false);
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "export") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "env") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (true);
	return (false);
}

int	execute_builtin(char **arg_list, t_data *data)
{
	if (!arg_list || !arg_list[0])
		return (0);
	if (ft_strcmp(arg_list[0], "echo") == 0)
		return (my_echo(arg_list), 0);
	if (ft_strcmp(arg_list[0], "cd") == 0)
		return (my_cd(arg_list, data));
	if (ft_strcmp(arg_list[0], "pwd") == 0)
		return (my_pwd(), 0);
	if (ft_strcmp(arg_list[0], "export") == 0)
		return (my_export(arg_list, data));
	if (ft_strcmp(arg_list[0], "unset") == 0)
		return (my_unset(arg_list, data));
	if (ft_strcmp(arg_list[0], "env") == 0)
		return (my_environ(data->env), 0);
	if (ft_strcmp(arg_list[0], "exit") == 0)
		return (my_exit(arg_list, data));
	return (-1);
}