/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:50:37 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/17 16:43:30 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**tokens_to_args(t_token *tokens)
{
	t_token	*temp;
	char	**args;
	int		count;
	int		i;

	i = 0;
	count = 0;
	temp = tokens;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	temp = tokens;
	i = 0;
	while (i < count)
	{
		args[i++] = temp->str;
		temp = temp->next;
	}
	args[i] = NULL;
	return (args);
}

static int	execute_builtin(char **arg_list, t_data *data)
{
	if (ft_strcmp(arg_list[0], "echo") == 0)
		return (my_echo(arg_list), 0);
	if (ft_strcmp(arg_list[0], "pwd") == 0)
		return (my_pwd(), 0);
	if (ft_strcmp(arg_list[0], "env") == 0)
		return (my_environ(data->env), 0);
	return (-1);
}

/*
** This is the routine for the parent process. It waits for the child
** and interprets its exit status.
*/
static int	parent_routine(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		return (128 + WTERMSIG(status));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

/*
** This is the routine for the child process. It sets signals
** and attempts to execute the command. It only returns on error.
*/
static void	child_routine(char *cmd_path, char **arg_list, char **envp)
{
	set_signals_for_child_process();
	execve(cmd_path, arg_list, envp);
	perror("minishell");
	free(cmd_path);
	mango_free(envp);
	exit(126);
}

/*
** This function is now much shorter. It prepares for the fork,
** forks, and then calls the appropriate routine for parent or child.
*/
static int	execute_external(char **arg_list, t_data *data)
{
	pid_t	pid;
	char	*cmd_path;
	char	**envp;

	cmd_path = get_cmd_path(arg_list[0], data->env);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(arg_list[0], 2);
		return (127);
	}
	envp = env_list_to_array(data->env);
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		free(cmd_path);
		mango_free(envp);
		return (1);
	}
	if (pid == 0)
		child_routine(cmd_path, arg_list, envp);
	free(cmd_path);
	mango_free(envp);
	return (parent_routine(pid));
}

void	setup_redirections(t_token *tokens)
{
	t_token	*current;
	int		fd;

	current = tokens;
	while (current)
	{
		if (current->type == REDIR_IN)
		{
			fd = open(current->str, O_RDONLY);
			if (fd < 0)
			{
				perror("minishell: open");
				return ;
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		current = current->next;
	}
}

bool	execution(t_data *data, t_token *tokens)
{
	char	**arg_list;
	int		stdin_backup;

	stdin_backup = dup(STDIN_FILENO);
	setup_redirections(tokens);
	arg_list = tokens_to_args(tokens);
	if (!arg_list || !arg_list[0])
	{
		free(arg_list);
		dup2(stdin_backup, STDIN_FILENO);
		close(stdin_backup);
		return (false);
	}
	data->last_exit_status = execute_builtin(arg_list, data);
	if (data->last_exit_status == -1)
		data->last_exit_status = execute_external(arg_list, data);
	free(arg_list);
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
	return (true);
}
