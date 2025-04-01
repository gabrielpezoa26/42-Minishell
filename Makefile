# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/01 16:33:05 by gcesar-n          #+#    #+#              #
#    Updated: 2025/04/01 16:41:35 by gcesar-n         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

# CFLAGS = -Wall -Werror -Wextra

SRCS = src/main.cc

OBJ_DIR = objects

OBJS = $(OBJ_DIR)/main.o

all: $(NAME)

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -Llibft -lft

#compilaa
$(OBJ_DIR)/main.o: src/main.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c src/main.c -o $(OBJ_DIR)/main.o

#objects
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)


libft/libft.a:
	make -C libft

clean:
	rm -rf $(OBJ_DIR)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all