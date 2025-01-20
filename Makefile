# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/18 18:22:57 by kzinchuk          #+#    #+#              #
#    Updated: 2025/01/20 15:10:28 by kzinchuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME := fdf
CC := cc
CFLAGS_DEV := -Wall -Werror -Wextra -Iinclude -I./MLX42/include -I./libft -Iget_next_line -DDEBUG=1 -g3 -v
CFLAGS_PROD := -Wall -Werror -Wextra -O3 -Wunreachable-code
CFLAGS = $(CFLAGS_DEV)

LIBFT_DIR := ./libft
LIBFT := $(LIBFT_DIR)/libft.a
LIBMLX := ./MLX42
LIBS := $(LIBFT) $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRCS = src/fdf.c src/color.c src/render.c src/parcer1.c \
       get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
OBJS= $(SRCS:.c=.o)

VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --

all: libft libmlx $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && cmake --build $(LIBMLX)/build --parallel
	@echo "MLX42 library build successfully"

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(NAME) built successfully"

prod:
	@$(MAKE) CFLAGS="$(CFLAGS_PROD)" all

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@echo "Cleaned object files and MLX42 build directory."

fclean: clean
	@rm -rf $(NAME)
	@echo "Cleaned executable and build files."

re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re libmlx