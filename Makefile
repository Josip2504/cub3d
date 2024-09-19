NAME = cub3d
CC = cc
CFLAGS = #-Wall -Werror -Wextra #-fsanitize=address
SRC_DIR = src
OBJ_DIR = obj


SRC = $(shell find $(SRC_DIR) -name "*.c")

OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

LIBFT_PATH = libft
LIBFT_H = -L$(LIBFT_PATH) -lft
INCLUDE = -Iinclude -I$(LIBFT_PATH) -I$(MLXDIR)/include

MLXDIR = lib/MLX42
MLX = -L$(MLXDIR)/build -lMLX42 -lglfw -lm

all: $(MLXDIR)/build/libmlx42.a $(NAME)


$(NAME): $(OBJ) libft/libft.a #$(MLXDIR)/build/libmlx42.a
	@$(CC) $(OBJ) $(LIBFT_H) $(MLX) -o $(NAME)
	@echo "Compiling $(NAME) completed successfully."

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

libft/libft.a:
	@$(MAKE) -C $(LIBFT_PATH)

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_PATH) clean
	@echo "Cleaning object files and libft..."

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@rm -f $(MLXDIR)/build/libmlx42.a
	@echo "Full clean complete."

re: fclean all

$(MLXDIR)/build/libmlx42.a:
	@if [ ! -f "$(MLXDIR)/build/libmlx42.a" ]; then \
		echo "Cloning and building MLX42..."; \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLXDIR); \
		cmake -B $(MLXDIR)/build $(MLXDIR); \
		cmake --build $(MLXDIR)/build -j4; \
		echo "MLX42 successfully built."; \
	fi

.PHONY: all clean fclean re
