/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:50:37 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/11 16:35:44 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * token_to_args -> converts the list of tokens to an **list
 * 
 * @tokens: the list of tokens to be converted
 * 
 * @return: the **list of arguments
 */
// char	**tokens_to_args(t_token *tokens)
// {
// 	t_token	*temp;
// 	char	**args;
// 	int		count;
// 	int		i;

// 	i = 0;
// 	count = 0;
// 	temp = tokens;
// 	while (temp)
// 	{
// 		count++;
// 		temp = temp->next;
// 	}
// 	args = malloc(sizeof(char *) * (count + 1));
// 	if (!args)
// 		return (NULL);
// 	temp = tokens;
// 	while (i < count)
// 	{
// 		args[i] = temp->str;
// 		temp = temp->next;
// 		i++;
// 	}
// 	args[i] = NULL;
// 	return (args);
// }

// static void	print_cmds(t_cmd *cmd)
// {
// 	int	i;

// 	while (cmd)
// 	{
// 		i = 0;
// 		while (cmd->args[i])
// 		{
// 			printf("%s\n", cmd->args[i]);
// 			i++;
// 		}
// 		printf("opa oia o pipe aeeee\n");
// 		cmd = cmd->next;
// 	}
// }

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
	if (ft_strcmp(arg_list[0], "echo") == 0)
		my_echo(arg_list);
	if (ft_strcmp(arg_list[0], "pwd") == 0)
		my_pwd();
	if (ft_strcmp(arg_list[0], "env") == 0)
		my_environ(data->env);
	free(arg_list);
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
	return (true);
}
