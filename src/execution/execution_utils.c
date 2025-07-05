/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:40:36 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/07/04 15:49:26 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	report_file_error(char *cmd_name, t_data *data)
{
	struct stat	file_stat;

	if (access(cmd_name, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_name, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		free_child(data, 127);
	}
	stat(cmd_name, &file_stat);
	if (S_ISDIR(file_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_name, STDERR_FILENO);
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
		free_child(data, 126);
	}
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putendl_fd(": Permission denied", STDERR_FILENO);
	free_child(data, 126);
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
		free_child(data, 127);
	}
}

int	wait_for_children(pid_t last_pid)
{
	int	status;
	int	last_status;

	if (last_pid == -1)
		return (0);
	waitpid(last_pid, &status, 0);
	last_status = get_exit_status(status);
	while (wait(NULL) > 0)
		;
	return (last_status);
}

void	execute_external_cmd(char *path, t_cmd *cmd, t_data *data)
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
		free(path);
		free_matrix(envp);
		free_child(data, 126);
	}
	else
	{
		perror(NULL);
		free(path);
		free_matrix(envp);
		free_child(data, 127);
	}
	free_pointers(path, envp);
}

pid_t	create_pipeline(t_cmd *cmds, t_data *data)
{
	int		pipe_fd[2];
	int		prev_read;
	pid_t	pid;

	prev_read = STDIN_FILENO;
	pid = -1;
	while (cmds)
	{
		if (cmds->next && pipe(pipe_fd) == -1)
			return (perror("minishell: pipe"), -1);
		pid = fork();
		if (pid == -1)
			return (perror("minishell: fork"), -1);
		if (pid == 0)
			child_process(cmds, data, pipe_fd, prev_read);
		if (prev_read != STDIN_FILENO)
			close(prev_read);
		if (cmds->next)
		{
			close(pipe_fd[1]);
			prev_read = pipe_fd[0];
		}
		cmds = cmds->next;
	}
	return (pid);
}
