/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:40:00 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/06/04 15:26:51 by gcesar-n         ###   ########.fr       */
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

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	t_env	*env;
	t_env	*locals;
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
	int				index;
	struct s_token	*next;
}	t_token;

/*---------PARSER---------*/
bool	check_argc(int argc);
bool	parse_input(t_data *data, t_token **tokens, t_env **my_envp);
bool	validate_tokens(t_token **tokens);

/*---------UTILS---------*/
void	exit_minishell(t_data *data, char *message);
bool	init_data(t_data *data);
void	mango_free(char **matrix);

/*---------UTILS-PARSER---------*/
void	*ft_calloc(size_t item_count, size_t size_bytes);
void	*ft_malloc(size_t size, size_t type);
bool	verify_space(char *str);
char	*trim_space(char *string);

/*-----------TOKEN---------------*/
bool	convert_token(t_data *data, t_token **tokens);
void	init_tokens(t_token **token, char *input);
bool	token_operators(char *input);
bool	are_quotes_valid(char *input);

/*--------TOKEN_INIT_UTILS----------*/
bool	str_string_append(char **input, char **str, bool *is_expandable);

/*-----------TOKEN_NODES---------------*/
void	append_token(t_token **tokens, char *content, int op, bool is_expand);
void	add_back(t_token **token, t_token *node);
t_token	*last_token(t_token *token);

/*----------UTILS-TOKEN-------------*/
bool	is_operator(char input);
bool	is_wspace(char input);
bool	is_quote(char input);
char	*ft_join(const char *s1, char s2);
char	*ft_strdup_char(int *index);

/*-------TOKEN_NODES_UTILS-----------*/
void	free_tokens(t_token **tokens);
void	free_env(t_env **my_env);

/*----------VERIFY_TOKENS----------*/
bool	token_valid(t_token **tokens);

/*--------------ENVP----------------*/
void	search_dollar(t_env *env, t_env *locals, t_token **tokens);
void	env_dup(char **envp, t_env **my_env);
size_t	count_rows(char **s);
bool	char_expandable(char c);
void	ft_strcat(char *dst, const char *src, size_t index);
bool	update_env(t_env **env, char *assignment);

/*------------ENVP-NODE-------------*/
void	append_env(t_env **my_env, char *content);
void	add_back_env(t_env **my_env, t_env *node);
void	handle_assignments(t_token *tokens, t_env **env);

/*--------------EXECUTION----------------*/
bool	execution(t_data *data, t_token *tokens);

/*--------------BUILT-INS----------------*/
bool	my_pwd(void);
bool	my_echo(char **args);
bool	my_env(t_data *data);

#endif