/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:50:37 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/27 14:59:44 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	execute_command(t_cmd *cmd, t_data *data)
{
	char	*path;

	if (!cmd->args || !cmd->args[0] || cmd->args[0][0] == '\0')
		child_cleanup(data, 0);
	if (is_builtin(cmd->args[0]))
		execute_builtin_child(cmd, data);
	path = get_cmd_path(cmd->args[0], data->env);
	if (!path)
		handle_path_error(cmd->args[0], data);
	execute_external(path, cmd, data);
}

void	child_process(t_cmd *cmd, t_data *data, int *pfd, int prev_read)
{
	set_signals_for_child_process();
	if (prev_read != STDIN_FILENO)
	{
		dup2(prev_read, STDIN_FILENO);
		close(prev_read);
	}
	if (cmd->next)
	{
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
	}
	execute_command(cmd, data);
}

static int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		return (128 + WTERMSIG(status));
	}
	return (1);
}

static int	wait_for_children(pid_t last_pid)
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

int	execution(t_cmd *cmds, t_data *data)
{
	pid_t	last_pid;

	if (!cmds->next && cmds->args[0] && is_builtin(cmds->args[0])
		&& !cmds->redirections)
		return (execute_builtin(cmds->args, data));
	last_pid = create_pipeline(cmds, data);
	if (last_pid == -1)
		return (1);
	return (wait_for_children(last_pid));
}
