NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(INCLUDES)

INCLUDES = includes
LIBFT_DIR = $(INCLUDES)/libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = src
PARSER_DIR = $(SRC_DIR)/parser
EXEC_DIR = $(SRC_DIR)/executor
TOKEN_DIR = $(SRC_DIR)/token
UTILS_DIR = $(SRC_DIR)/utils
ENV_DIR = $(SRC_DIR)/env
VRF_TOKEN = $(SRC_DIR)/verify_tokens
BUILTINS_DIR = $(SRC_DIR)/builtins
EXEC_DIR = $(SRC_DIR)/execution

OBJ_DIR = objects

SRCS = $(SRC_DIR)/main.c \
		$(PARSER_DIR)/parse_input.c \
		$(TOKEN_DIR)/token.c \
		$(TOKEN_DIR)/operators.c \
		$(TOKEN_DIR)/quotes.c \
		$(TOKEN_DIR)/token_nodes.c \
		$(TOKEN_DIR)/token_init.c \
		$(TOKEN_DIR)/token_init_utils.c \
		$(TOKEN_DIR)/token_utils.c \
		$(UTILS_DIR)/utils_parser.c \
		$(UTILS_DIR)/cleanup.c \
		$(PARSER_DIR)/parse_tokens.c \
		$(VRF_TOKEN)/verify.c \
		$(ENV_DIR)/env.c \
		$(ENV_DIR)/env_utils.c \
		$(ENV_DIR)/env_nodes.c \
		$(ENV_DIR)/assign_env_var.c \
		$(BUILTINS_DIR)/my_pwd.c \
		$(BUILTINS_DIR)/my_echo.c \
		$(BUILTINS_DIR)/my_env.c \
		$(EXEC_DIR)/execution.c \


OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

SUPP = supp.supp

val: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=$(SUPP) ./$(NAME)

.PHONY: all clean fclean re
