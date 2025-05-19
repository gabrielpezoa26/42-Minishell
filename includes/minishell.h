/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:40:00 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/05/19 16:19:26 by gcesar-n         ###   ########.fr       */
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
# define TOKEN "bash: syntax error"

typedef struct s_data
{
	char	**envp;
	char	*input;
	char	*token;
	bool	exec;
}	t_data;

typedef enum e_token_types
{
	WORD, // WORD
	PIPE, // |
	REDIR_IN, //<
	REDIR_OUT, //>
	REDIR_APPEND, //>>
	REDIR_DELIMITER, //<<
}	t_type;

typedef struct s_token
{
	char			*str;
	t_type			type;
	bool			is_expandable;
	int				*array;
	struct s_token	*next;
}	t_token;

/*---------PARSER---------*/
bool	check_argc(int argc);
void	parse_input(t_data *data, t_token **tokens);
bool	validate_tokens(t_token **tokens);

/*---------UTILS---------*/
void	exit_minishell(t_data *data, char *message);
bool	init_data(t_data *data);

/*---------UTILS-PARSER---------*/
void	*ft_calloc(size_t item_count, size_t size_bytes);
void	*ft_malloc(size_t size);
bool	verify_space(char *str);
char	*trim_space(char *string);

/*-----------TOKEN---------------*/
bool	convert_token(t_data *data, t_token **tokens);
void	init_tokens(t_token **token, char *input);
bool	token_operators(char *input);
bool	are_quotes_valid(char *input);

/*-----------TOKEN_NODES---------------*/
void	append_node(t_token **tokens, char *content, int operator);
void	add_back(t_token **token, t_token *node);

/*----------UTILS-TOKEN-------------*/
bool	is_operator(char input);
bool	is_wspace(char input);
bool	is_quote(char input);
char	*ft_join(const char *s1, char s2);
char	*ft_strdup_char(int *index);

/*-------TOKEN_NODES_UTILS-----------*/
int		word_count(char *str_token);
void	find_dollar_sign(int v[], char *str, int size);
void	free_tokens(t_token *tokens);

/*----------VERIFY_TOKENS----------*/
bool	token_valid(t_token **tokens);

#endif