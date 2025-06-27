/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:51:06 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/27 14:51:18 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* redirections.c                                     :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/06/27 15:01:00 by gcesar-n          #+#    #+#             */
/* Updated: 2025/06/27 15:01:00 by gcesar-n         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
