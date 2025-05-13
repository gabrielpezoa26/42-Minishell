/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:40:00 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/13 12:14:23 by dteruya          ###   ########.fr       */
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

/*--------MACROS-------*/
#define TOKEN ""

typedef struct s_data
{
	char	**envp;
	char	*input;
	char	*token;
	bool	exec;
}	t_data;

typedef struct s_token
{
	char			*token_id;
	int				type_operator;
	bool			variable_exists;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

enum e_token_types
{
	SPACES = 1,
	WORD,
	VAR,
	PIPE,
};

/*---------PARSER---------*/
bool	check_argc(int argc);
void	parse_input(t_data *data);

/*---------UTILS---------*/
void	exit_minishell(t_data *data, char *message);
bool	init_data(t_data *data);
// bool	init_token(t_token *token);

/*---------UTILS-PARSER---------*/
void	*ft_calloc(size_t item_count, size_t size_bytes);
void	*ft_malloc(size_t size);
bool	verify_space(char *str);
char	*trim_space(char *string);

/*-----------TOKEN---------------*/
bool	to_token(t_data *data);

bool	token_operators(char *input);

bool	are_quotes_valid(char *input);

#endif