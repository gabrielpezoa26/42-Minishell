/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:40:41 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/07/03 15:49:34 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	heredoc_loop(int fd, char *delimiter, bool is_eof, t_data *data)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (get_data(false, NULL)->last_exit_status != 130)
				ft_putstr_fd("minishell: warning: here-document "
					"delimited by end-of-file\n", 2);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (is_eof)
			search_dollar_heredoc(&line, data->env);
		ft_putendl_fd(line, fd);
		free(line);
	}
}

static void	run_hdoc_loop(int tmp_fd, char *delimiter, bool eof, t_data *data)
{
	int	stdin_backup;

	stdin_backup = dup(STDIN_FILENO);
	set_heredoc_signals();
	heredoc_loop(tmp_fd, delimiter, eof, data);
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
	setup_interactive_signals();
}

char	*read_and_write_hdoc(char *delimiter, bool is_eof, t_data *data)
{
	int		tmp_fd;
	char	*tmp_filename;

	tmp_filename = get_heredoc_filename();
	if (!tmp_filename)
		return (NULL);
	tmp_fd = open(tmp_filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (tmp_fd < 0)
	{
		perror("minishell: open");
		free(tmp_filename);
		return (NULL);
	}
	run_hdoc_loop(tmp_fd, delimiter, is_eof, data);
	close(tmp_fd);
	if (data->last_exit_status == 130)
	{
		unlink(tmp_filename);
		free(tmp_filename);
		return (NULL);
	}
	return (tmp_filename);
}

bool	process_heredoc_token(t_token *current, t_data *data)
{
	t_token	*delimiter_token;
	char	*tmp_filename;

	delimiter_token = current->next;
	if (delimiter_token && delimiter_token->type == WORD)
	{
		tmp_filename = read_and_write_hdoc(delimiter_token->str,
				delimiter_token->is_eof, data);
		if (tmp_filename)
		{
			current->type = REDIR_IN;
			free(current->str);
			current->str = ft_strdup("<");
			free(delimiter_token->str);
			delimiter_token->str = tmp_filename;
		}
		else
			return (false);
	}
	return (true);
}

void	cleanup_heredocs(t_token *tokens)
{
	t_token	*current;
	char	*prefix;

	prefix = "/tmp/minishell-heredoc-";
	current = tokens;
	while (current)
	{
		if (current->type == REDIR_IN && current->next)
		{
			if (ft_strncmp(current->next->str, prefix, ft_strlen(prefix)) == 0)
				unlink(current->next->str);
		}
		current = current->next;
	}
}
