# colors
GREEN  := \033[32m
GREEN_BG := \033[42m
BOLD := \033[1m
PURPLE := \033[35m
RESET  := \033[0m

NAME := FDF
CC := cc
CFLAGS_DEV := -Wall -Werror -Wextra -Iinclude -I./MLX42/include -I./libft -Iget_next_line -DDEBUG=1 -g3 -v 
CFLAGS_PROD := -Wall -Werror -Wextra -O3 -Wunreachable-code 
CFLAGS = $(CFLAGS_DEV)

LIBFT_DIR := ./libft
LIBFT := $(LIBFT_DIR)/libft.a
LIBMLX := ./MLX42
LIBS := $(LIBFT) $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

FDF = src/fdf/main.c src/fdf/fdf.c src/fdf/errors.c src/fdf/key_controls.c
PARSER = src/parser/parser.c src/parser/create_node.c src/parser/map_check.c src/parser/parser_utils.c
RENDER = src/render/render.c src/render/color.c src/render/render_utils.c src/render/bresenham_utils.c
GNL = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

SRCS =	$(FDF) $(PARSER) $(RENDER) $(GNL)

BUILD_DIR = build
OBJS= $(SRCS:src/%.c=$(BUILD_DIR)/%.o)

VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --

OBJ_DIRS = $(sort $(dir $(OBJS)))

all: libft libmlx $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && cmake --build $(LIBMLX)/build --parallel
	@echo "MLX42 library build successfully"

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -v $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(BOLD)$(NAME)$(RESET)$(GREEN) built successfully$(RESET)"

prod:
	@$(MAKE) CFLAGS="$(CFLAGS_PROD)" all

clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(LIBMLX)/build
	@echo "$(PURPLE)Cleaned $(BOLD)$(NAME)$(RESET)$(PURPLE) object files and MLX42 build directory."

fclean: clean
	@rm -rf $(NAME)
	@echo "Cleaned executable and build files."

re: fclean all

$(BUILD_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIRS)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re libmlx