/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:06:40 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/07/02 13:00:45 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	(*del)(lst->content);
	free(lst);
}

void	del_node(t_token **tokens, t_token *to_delete, void (*del)(void *))
{
	t_token	*current;
	t_token	*prev;

	if (!tokens || !*tokens || !to_delete || !del)
		return ;
	if (*tokens == to_delete)
	{
		*tokens = to_delete->next;
		delone((t_list *)to_delete, del);
		return ;
	}
	prev = *tokens;
	current = (*tokens)->next;
	while (current)
	{
		if (current == to_delete)
		{
			prev->next = current->next;
			delone((t_list *)current, del);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

t_data	*get_data(bool set, t_data *data_ptr)
{
	static t_data	*static_data_ptr = NULL;

	if (set)
		static_data_ptr = data_ptr;
	return (static_data_ptr);
}

char	*get_heredoc_filename(void)
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
