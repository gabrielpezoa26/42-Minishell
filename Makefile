NAME = minishell

CC = cc
# CFLAGS = -Wall -Wextra -Werror -I $(INCLUDES)

INCLUDES = includes
LIBFT_DIR = $(INCLUDES)/libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = src
PARSER_DIR = $(SRC_DIR)/parser
EXEC_DIR = $(SRC_DIR)/executor
UTILS_DIR = $(SRC_DIR)/utils

OBJ_DIR = objects

SRCS = $(SRC_DIR)/main.c \
		$(PARSER_DIR)/parser.c \
		$(UTILS_DIR)/utils_parser.c \
		$(UTILS_DIR)/cleanup.c

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

.PHONY: all clean fclean re
