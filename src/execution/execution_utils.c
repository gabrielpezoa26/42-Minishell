/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:40:36 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/27 14:45:19 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// a gnt divide a funcao de 80 linha e joga as auxiliar aq

static void	report_file_error(char *cmd_name, t_data *data)
{
	struct stat	file_stat;

	if (access(cmd_name, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_name, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		child_cleanup(data, 127);
	}
	stat(cmd_name, &file_stat);
	if (S_ISDIR(file_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_name, STDERR_FILENO);
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
		child_cleanup(data, 126);
	}
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putendl_fd(": Permission denied", STDERR_FILENO);
	child_cleanup(data, 126);
}

void	handle_path_error(char *cmd_name, t_data *data)
{
	if (ft_strchr(cmd_name, '/'))
		report_file_error(cmd_name, data);
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_name, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		child_cleanup(data, 127);
	}
}

void	execute_builtin_child(t_cmd *cmd, t_data *data)
{
	int	builtin_status;

	setup_redirections(cmd->redirections);
	builtin_status = execute_builtin(cmd->args, data);
	child_cleanup(data, builtin_status);
}

void	execute_external(char *path, t_cmd *cmd, t_data *data)
{
	char	**envp;

	setup_redirections(cmd->redirections);
	envp = env_list_to_array(data->env);
	execve(path, cmd->args, envp);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->args[0], STDERR_FILENO);
	if (errno == EACCES || errno == EISDIR)
	{
		if (errno == EACCES)
			ft_putendl_fd(": Permission denied", STDERR_FILENO);
		if (errno == EISDIR)
			ft_putendl_fd(": Is a directory", STDERR_FILENO);
		child_cleanup(data, 126);
	}
	else
	{
		perror(NULL);
		child_cleanup(data, 127);
	}
	free(path);
	mango_free(envp);
}
