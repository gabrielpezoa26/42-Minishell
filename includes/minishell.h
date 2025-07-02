/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:40:00 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/07/02 15:03:00 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/stat.h>
# include <errno.h>
# include <sys/wait.h>

/*--------MACROS-------*/
# define TOKEN "bash: syntax error"

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}	t_env;

typedef enum e_token_types
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_DELIMITER,
}	t_type;

typedef struct s_token
{
	char			*str;
	t_type			type;
	bool			is_expandable;
	bool			is_eof;
	int				index;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_type			type;
	char			*file;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_list			*redirections;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	t_env	*env;
	t_env	*locals;
	char	*input;
	t_token	*tokens;
	t_cmd	*cmds;
	bool	exec;
	int		last_exit_status;
}	t_data;

/*---------SIGNALS---------*/
void	setup_interactive_signals(void);
void	set_signals_for_child_process(void);

/*---------PARSER---------*/
bool	check_argc(int argc);
bool	is_all_spaces(char *input);
bool	is_all_quotes(char *input);
void	handle_all_quotes(void);
bool	parse_input(t_data *data, t_token **tokens, t_env **my_envp);
bool	validate_tokens(t_token **tokens);
t_cmd	*parser(t_token *tokens);

/*-----------TOKEN---------------*/
bool	convert_token(t_data *data, t_token **tokens);
void	init_tokens(t_token **token, char *input);
bool	token_operators(char *input);
bool	are_quotes_valid(char *input);
bool	str_append(char **input, char **str, bool *is_exp, char quote);
void	append_token(t_token **tokens, char *content, int op, bool is_expand);
void	add_back(t_token **token, t_token *node);
t_token	*last_token(t_token *token);
bool	is_operator(char input);
bool	is_wspace(char input);
bool	is_quote(char input);
char	*ft_join(const char *s1, char s2);
char	*ft_strdup_char(int *index);
void	free_tokens(t_token **tokens);
void	free_env(t_env **my_env);
char	*handle_eof(char **input, char quote, bool *is_expand, int *flag);
char	*str_string(char **input, bool *is_expandable);
char	*str_operator(char **input, int *op);
char	*get_double_op(char **input, int *op);
char	*append_until_quote(char **input, char *str, char quote);

/*--------------ENVP----------------*/
void	search_dollar(t_data *data, t_token **tokens);
void	env_dup(char **envp, t_env **my_env);
size_t	count_rows(char **s);
bool	is_char_expandable(char c);
void	ft_strcat(char *dst, const char *src, size_t index);
void	append_env(t_env **my_env, char *content);
void	add_back_env(t_env **my_env, t_env *node);
void	handle_assignments(t_token *tokens, t_env **env);
char	*get_assignment_name(char *str);
bool	update_value(t_env **list, char *name, char *assignment);
bool	is_valid_assignment(char *str);
size_t	count_env_nodes(t_env *my_env);
char	**env_list_to_array(t_env *my_env);
char	*my_getenv(char *name, t_env *env, t_env *locals);

/*---------HEREDOC----------*/
bool	handle_heredocs(t_token **tokens, t_data *data);
char	*get_heredoc_filename(void);
bool	process_heredoc_token(t_token *current, t_data *data);
char	*read_and_write_hdoc(char *delimiter, bool is_eof, t_data *data);
void	search_dollar_heredoc(char **line, t_env *my_env);
void	cleanup_heredocs(t_token *tokens);
void	setup_heredoc_signals(void);

/*--------------BUILT-INS----------------*/
bool	my_pwd(void);
bool	my_echo(char **args);
bool	my_environ(t_env *my_env);
int		my_exit(char **args, t_data *data);
int		my_cd(char **args, t_data *data);
int		my_export(char **args, t_data *data);
int		my_unset(char **args, t_data *data);

/*--------------EXECUTION----------------*/
int		execution(t_cmd *cmds, t_data *data);
void	setup_redirections(t_list *redirections);
char	*get_cmd_path(char *cmd, t_env *my_env);
void	free_commands(t_cmd **commands);
bool	is_builtin(const char *cmd_name);
int		execute_builtin(char **arg_list, t_data *data);
void	handle_path_error(char *cmd_name, t_data *data);
void	execute_builtin_child(t_cmd *cmd, t_data *data);
void	execute_external(char *path, t_cmd *cmd, t_data *data);
pid_t	create_pipeline(t_cmd *cmds, t_data *data);
void	child_process(t_cmd *cmd, t_data *data, int *pfd, int prev_read);

/*---------UTILS---------*/
void	exit_minishell(t_data *data, int exit_code);
void	child_cleanup(t_data *data, int exit_code);
void	free_array(char **matrix);
void	*ft_calloc(size_t item_count, size_t size_bytes);
void	*ft_malloc(size_t size, size_t type);
bool	verify_space(char *str);
char	*trim_space(char *string);
void	clean_pointers(char *single_pointer, char **double_pointer);
void	ft_swap_str(char **a, char **b);
void	sort_env_array(char **array, size_t count);
char	**create_env_array(t_env *env, size_t *count);
void	print_sorted_env(t_env *env);
t_env	*find_node(t_env *list, const char *name);
t_data	*get_data(bool set, t_data *data_ptr);
void	delone(t_list *lst, void (*del)(void *));
void	del_node(t_token **tokens, t_token *to_delete, void (*del)(void *));

#endif
