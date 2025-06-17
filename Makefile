NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(INCLUDES) -g

INCLUDES = includes
LIBFT_DIR = $(INCLUDES)/libft
LIBFT = $(LIBFT_DIR)/libft.a
OBJ_DIR = objects

SRC_DIR = src
PARSER_DIR = $(SRC_DIR)/parser
TOKEN_DIR = $(SRC_DIR)/token
UTILS_DIR = $(SRC_DIR)/utils
ENV_DIR = $(SRC_DIR)/env
VRF_TOKEN = $(SRC_DIR)/verify_tokens
BUILTINS_DIR = $(SRC_DIR)/builtins
EXEC_DIR = $(SRC_DIR)/execution
SIGNALS_DIR = $(SRC_DIR)/signals

SRCS = $(SRC_DIR)/main.c \
		$(PARSER_DIR)/parse_input.c \
		$(PARSER_DIR)/heredoc.c \
		$(PARSER_DIR)/heredoc_utils.c \
		$(TOKEN_DIR)/token.c \
		$(TOKEN_DIR)/operators.c \
		$(TOKEN_DIR)/quotes.c \
		$(TOKEN_DIR)/token_nodes.c \
		$(TOKEN_DIR)/token_nodes_utils.c \
		$(TOKEN_DIR)/token_init.c \
		$(TOKEN_DIR)/token_init_utils.c \
		$(TOKEN_DIR)/token_utils.c \
		$(UTILS_DIR)/utils_parser.c \
		$(UTILS_DIR)/cleanup.c \
		$(PARSER_DIR)/parse_tokens.c \
		$(PARSER_DIR)/parser.c \
		$(VRF_TOKEN)/verify.c \
		$(ENV_DIR)/env.c \
		$(ENV_DIR)/env_utils.c \
		$(ENV_DIR)/env_nodes.c \
		$(ENV_DIR)/assign_env_var.c \
		$(BUILTINS_DIR)/my_pwd.c \
		$(BUILTINS_DIR)/my_echo.c \
		$(BUILTINS_DIR)/my_env.c \
		$(BUILTINS_DIR)/my_export.c \
		$(EXEC_DIR)/execution.c \
		$(EXEC_DIR)/cmd_nodes.c \
		$(EXEC_DIR)/cmd_nodes_utils.c \
		$(EXEC_DIR)/find_path.c \
		$(SIGNALS_DIR)/signals.c \

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) bonus --no-print-directory

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory

re: fclean all

SUPP = supp.supp
val: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=$(SUPP) ./$(NAME)

.PHONY: all clean fclean re val