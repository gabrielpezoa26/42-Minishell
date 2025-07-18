/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:51:06 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/07/08 19:26:30 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	open_file_for_redir(t_data *data, t_redir *redir)
{
	int	fd;

	if (redir->type == REDIR_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == REDIR_APPEND)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(redir->file, O_RDONLY);
	if (fd < 0)
	{
		perror("minishell");
		free_child(data, 1);
		exit(1);
	}
	return (fd);
}

static void	apply_redirection(int fd, t_type type)
{
	if (type == REDIR_IN || type == REDIR_DELIMITER)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	setup_redirections(t_data *data, t_list *redirections)
{
	t_list	*current;
	t_redir	*redir;
	int		fd;

	current = redirections;
	while (current)
	{
		redir = (t_redir *)current->content;
		fd = open_file_for_redir(data, redir);
		apply_redirection(fd, redir->type);
		current = current->next;
	}
}
