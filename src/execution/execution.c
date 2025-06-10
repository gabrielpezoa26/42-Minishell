/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:50:37 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/10 19:58:23 by dteruya          ###   ########.fr       */
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

void	init_cmds(t_cmd **cmds, t_token *tokens)
{
	append_cmd(cmds, tokens);
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			tokens = tokens->next;
			append_cmd(cmds, tokens);
		}
		tokens = tokens->next;
	}
	// print_cmds(cmds);
}

/**
 * execution -> identifies a built-in and calls the responsible function
 * 
 * @data: a pointer to t_data
 * @tokens: pointer to t_token, lol
 * 
 * @return: true if deu bom
 */

static bool	is_builtin(char *command)
{
	if (ft_strcmp("echo", command) == 0)
		return (true);
	if (ft_strcmp("pwd", command) == 0)
		return (true);
	if (ft_strcmp("env", command) == 0)
		return (true);
	if (ft_strcmp("export", command) == 0)
		return (true);
	return (false);
}

static void execute_builtin(t_env *my_env, t_cmd *command)
{
	
	if (ft_strcmp(command->name, "echo") == 0)
		my_echo(command->args);
	if (ft_strcmp(command->name, "pwd") == 0)
		my_pwd();
	if (ft_strcmp(command->name, "env") == 0)
		my_environ(my_env);
	if (ft_strcmp(command->name, "export") == 0 && command->name)
		my_export(my_env, *command->args);
}

bool	execution(t_env *my_env, t_token *tokens)
{
	t_cmd *cmds = NULL;

	init_cmds(&cmds, tokens);
	if (is_builtin(cmds->name))
		execute_builtin(my_env, cmds);
	else
		printf("aaaaa\n");
		// execute_external(cmd);
	free_cmd(&cmds);
	return (true);
}


// if (is_builtin(cmd->name))
//     execute_builtin(cmd);    // Chama sua função
// else
//     execute_external(cmd);   // Usa execve()