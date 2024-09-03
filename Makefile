# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 10:47:42 by jsamardz          #+#    #+#              #
#    Updated: 2024/09/03 11:43:07 by jsamardz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC_DIR = src
OBJ_DIR = obj
SRC = $(addprefix src/, main.c)
OBJ = $(SRC:src/%.c=obj/%.o)
LIBFT_PATH = libft
LIBFT_H = -L$(LIBFT_PATH) -lft
INCLUDE = -Iinclude -I$(LIBFT_PATH)

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJ) libft/libft.a
	@$(CC) $(OBJ) $(LIBFT_H) -o $(NAME)
	@echo "Compiling\n$(NAME) compiled successul"

libft/libft.a:
	@make -C libft

clean:
	@rm -f $(OBJ)
	@make -C libft clean
	@echo "Cleaning"

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean
	@echo "Removing $(NAME)"

re: fclean all

.PHONY: all clean fclean re obj
