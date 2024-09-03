# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 14:39:19 by jsamardz          #+#    #+#              #
#    Updated: 2024/09/03 11:05:37 by jsamardz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra
CC = gcc
SRC = ft_strlen.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
ft_isprint.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strncmp.c ft_memset.c \
ft_bzero.c ft_memmove.c ft_memchr.c ft_strrchr.c ft_memcpy.c ft_strlcpy.c \
ft_strlcat.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_strmapi.c ft_striteri.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_split.c \
ft_printf.c print_format.c print_char.c print_str.c print_digit.c print_x.c \
print_ptr.c get_next_line.c get_next_line_utils.c
OBJ = $(SRC:.c=.o)
NAME = libft.a

all: ${NAME}

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f ${OBJ}

fclean:
	@rm -f ${NAME}
	@rm -f ${OBJ}

re: fclean all
.PHONY: all clean fclean re