/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:50:37 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/23 16:18:43 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	is_builtin(const char *cmd_name)
{
	if (!cmd_name)
		return (false);
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "env") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (true);
	return (false);
}

static int	execute_builtin(char **arg_list, t_data *data)
{
	if (!arg_list || !arg_list[0])
		return (0);
	if (ft_strcmp(arg_list[0], "echo") == 0)
		return (my_echo(arg_list), 0);
	if (ft_strcmp(arg_list[0], "pwd") == 0)
		return (my_pwd(), 0);
	if (ft_strcmp(arg_list[0], "env") == 0)
		return (my_environ(data->env), 0);
	if (ft_strcmp(arg_list[0], "exit") == 0)
		return (my_exit(arg_list, data));
	return (-1);
}

void	setup_redirections(t_list *redirections)
{
	t_list	*current;
	t_redir	*redir;
	int		fd;

	current = redirections;
	while (current)
	{
		redir = (t_redir *)current->content;
		if (redir->type == REDIR_OUT)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == REDIR_APPEND)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(redir->file, O_RDONLY);
		if (fd < 0)
		{
			perror("minishell");
			exit(1);
		}
		if (redir->type == REDIR_IN || redir->type == REDIR_DELIMITER)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		current = current->next;
	}
}

static void	execute_command(t_cmd *cmd, t_data *data)
{
	char	*path;
	char	**envp;
	int		status;

	if (!cmd->args || !cmd->args[0])
		child_cleanup(data, 0);
	setup_redirections(cmd->redirections);
	status = execute_builtin(cmd->args, data);
	if (status != -1)
		child_cleanup(data, status);
	path = get_cmd_path(cmd->args[0], data->env);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd->args[0], 2);
		child_cleanup(data, 127);
	}
	envp = env_list_to_array(data->env);
	execve(path, cmd->args, envp);
	perror("minishell");
	free(path);
	mango_free(envp);
	child_cleanup(data, 126);
}

static void	child_process(t_cmd *cmd, t_data *data, int *pfd, int prev_read_end)
{
	set_signals_for_child_process();
	if (prev_read_end != STDIN_FILENO)
	{
		dup2(prev_read_end, STDIN_FILENO);
		close(prev_read_end);
	}
	if (cmd->next)
	{
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
	}
	execute_command(cmd, data);
}

static int	wait_for_pipeline(pid_t last_pid)
{
	int	status;
	int	last_status;

	if (last_pid == -1)
		return (0);
	waitpid(last_pid, &status, 0);
	if (WIFEXITED(status))
		last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		last_status = 128 + WTERMSIG(status);
	}
	else
		last_status = 1;
	while (wait(NULL) > 0)
		;
	return (last_status);
}

int	execution(t_cmd *cmds, t_data *data)
{
	int		pfd[2];
	int		prev_read_end;
	pid_t	pid;

	if (!cmds->next && cmds->args[0] && is_builtin(cmds->args[0]))
		return (execute_builtin(cmds->args, data));
	prev_read_end = STDIN_FILENO;
	pid = -1;
	while (cmds)
	{
		if (cmds->next && pipe(pfd) == -1)
			return (perror("minishell: pipe"), 1);
		pid = fork();
		if (pid == -1)
			return (perror("minishell: fork"), 1);
		if (pid == 0)
			child_process(cmds, data, pfd, prev_read_end);
		if (prev_read_end != STDIN_FILENO)
			close(prev_read_end);
		if (cmds->next)
		{
			close(pfd[1]);
			prev_read_end = pfd[0];
		}
		cmds = cmds->next;
	}
	return (wait_for_pipeline(pid));
}
