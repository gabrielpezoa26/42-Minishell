/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:22:33 by dteruya           #+#    #+#             */
/*   Updated: 2025/04/07 15:20:17 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int verify_command(char *rl)
{
char	*path_env;
char	**path;
char	*full_cmd;
int		i;

path_env = getenv("PATH");
path = ft_split(path_env, ':');
i = 0;
while (path[i])
{
	full_cmd = join(paths[i], "ls");
	if (access(full_cmd, X_OK) == 0)
		execve(full_cmd, args, envp);
	i++;
}
}

int validate_input(char **argv)
{
	char *rl;

	while(1)
	{
		rl = readline("minishell$ ");
		if (rl)
		{
			if (verify_command(rl))
				ft_printf("%s\n", rl);
			add_history(rl);
		}
		else
			exit(0);
	}
	return (1);
}

