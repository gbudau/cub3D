# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/01 17:44:30 by gbudau            #+#    #+#              #
#    Updated: 2020/07/29 21:04:23 by gbudau           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address 
OFLAGS = -c -o
LFLAGS = -lmlx -lft -lXext -lX11 -lm
RMF = rm -rf

SRC_DIR = src
LIB_DIR = lib
LIBFT_DIR = libft
MLX_DIR = minilibx-linux
OBJ_DIR := obj
INC_DIR = include

_OBJ = cub3d.o image_utils.o save_bitmap.o \
	   parse.o boundary_fill.o initialize.o sprites.o hooks.o \
	   utils.o minimap.o move_player.o raycast.o quit.o check_args.o \
	   project_walls.o project_walls_utils.o raycast_horizontal.o \
	   raycast_vertical.o parse_utils.o parse_grid.o save_grid.o \
	   parse_resolution.o parse_color.o parse_texture.o
OBJ := $(patsubst %, $(OBJ_DIR)/%, $(_OBJ))

_DEPS = cub3d.h libft.h
DEPS := $(patsubst %, $(INC_DIR)/%, $(_DEPS))

.PHONY: all
all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) $(OFLAGS) $@ $<

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(NAME): $(OBJ)
	make -C $(LIB_DIR)/$(MLX_DIR) 2>/dev/null
	make -C $(LIB_DIR)/$(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -I/$(INC_DIR) -L$(LIB_DIR)/$(MLX_DIR) -L$(LIB_DIR)/$(LIBFT_DIR) $(LFLAGS)

.PHONY: clean
clean:
	make -C $(LIB_DIR)/$(LIBFT_DIR) fclean
	make -C $(LIB_DIR)/$(MLX_DIR) clean
	$(RMF) $(OBJ_DIR)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all
