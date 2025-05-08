/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:40:00 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/07 22:51:52 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_data
{
	char	**envp;
	char	*input;
	char	*token;
}	t_mango;

// typedef struct s_token
// {
// 	char	*blablabla;
// }	t_token;

/*---------PARSER---------*/
bool	basic_check(int argc, char **argv);
bool	parse_input(t_mango *mango);

/*------UTILS-PARSER-------*/
bool	verify_space(char *str);
bool	init_data(t_mango *mango);
// char	*ft_malloc(char *to_malloc);  //falta consertar

/*------CLEAN-------*/
void	exit_minishell(t_mango *mango, char *message);

#endif