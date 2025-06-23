/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:15:19 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/23 17:38:23 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_env_var(t_env **list, const char *name, const char *value)
{
	char	*assignment;
	char	*name_part;
	char	*var_name;

	if (!value)
		return ;
	name_part = ft_strjoin(name, "=");
	assignment = ft_strjoin(name_part, value);
	free(name_part);
	var_name = get_assignment_name(assignment);
	if (!update_value(list, var_name, assignment))
		append_env(list, assignment);
	free(var_name);
	free(assignment);
}

static void	update_pwd_vars(t_data *data)
{
	char	*cwd;
	char	*old_pwd;

	old_pwd = my_getenv("PWD", data->env, data->locals);
	set_env_var(&data->env, "OLDPWD", old_pwd);
	cwd = getcwd(NULL, 0);
	set_env_var(&data->env, "PWD", cwd);
	free(cwd);
}

static char	*get_target_path(char **args, t_data *data)
{
	char	*path;

	path = args[1];
	if (!path || ft_strcmp(path, "~") == 0)
	{
		path = my_getenv("HOME", data->env, data->locals);
		if (!path)
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	}
	else if (ft_strcmp(path, "-") == 0)
	{
		path = my_getenv("OLDPWD", data->env, data->locals);
		if (!path)
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		else
			ft_putendl_fd(path, 1);
	}
	return (path);
}

int	my_cd(char **args, t_data *data)
{
	char	*path;
	int		count;

	count = 0;
	while (args[count])
		count++;
	if (count > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	path = get_target_path(args, data);
	if (!path)
		return (1);
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		return (1);
	}
	update_pwd_vars(data);
	return (0);
}
