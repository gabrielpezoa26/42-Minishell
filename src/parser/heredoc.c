/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:40:41 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/12 18:39:20 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_heredoc_filename(void)
{
	char	*filename;
	char	*pid_str;

	pid_str = ft_itoa(getpid());
	if (!pid_str)
		return (NULL);
	filename = ft_strjoin("/tmp/minishell-heredoc-", pid_str);
	free(pid_str);
	return (filename);
}

static void	heredoc_loop(int fd, char *delimiter, bool is_EOF, t_env *my_env)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0) //colocar o sinal aqui SIGINT
		{
			if (line)
				free(line);
			break ;
		}
		if (is_EOF)
			search_dollar_heredoc(&line, my_env);
		printf("%s\n", line);
		ft_putendl_fd(line, fd);
		free(line);
	}
}

static char	*read_and_write_hdoc(char *delimiter, bool is_eof, t_env *my_env)
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
	heredoc_loop(tmp_fd, delimiter, is_eof, my_env);
	close(tmp_fd);
	return (tmp_filename);
}

void	handle_heredocs(t_token **tokens, t_env *my_env)
{
	t_token	*current;
	t_token	*delimiter_token;
	char	*tmp_filename;

	current = *tokens;
	while (current)
	{
		if (current->type == REDIR_DELIMITER)
		{
			delimiter_token = current->next;
			if (delimiter_token && delimiter_token->type == WORD)
			{
				tmp_filename = read_and_write_hdoc(delimiter_token->str, delimiter_token->is_eof, my_env);
				free(current->str);
				current->str = tmp_filename;
				current->type = REDIR_IN;
				current->next = delimiter_token->next;
				free(delimiter_token->str);
				free(delimiter_token);
			}
		}
		current = current->next;
	}
}

void	cleanup_heredocs(t_token *tokens)
{
	t_token	*current;
	char	*prefix;

	prefix = "/tmp/minishell-heredoc-";
	current = tokens;
	while (current)
	{
		if (current->type == REDIR_IN)
		{
			if (ft_strncmp(current->str, prefix, ft_strlen(prefix)) == 0)
				unlink(current->str);
		}
		current = current->next;
	}
}
