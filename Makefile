# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/01 17:44:30 by gbudau            #+#    #+#              #
#    Updated: 2020/08/06 14:31:51 by gbudau           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAME_BONUS = cub3D_bonus
CC = gcc
CFLAGS = -Wall -Werror -Wextra -O3
OFLAGS = -c -o
UNAME := $(shell uname)
RMF = rm -rf

SRC_DIR = src
SRC_DIR_BONUS = src_bonus
LIB_DIR = lib
LIBFT_DIR = libft
OBJ_DIR := obj
OBJ_DIR_BONUS := obj_bonus
INC_DIR = include
INC_DIR_BONUS = include_bonus

ifeq ($(UNAME),Linux)
	LFLAGS = -lmlx -lft -lXext -lX11 -lm
	MLX_DIR = minilibx-linux
endif
ifeq ($(UNAME),Darwin)
	LFLAGS = -lmlx -lft -framework OpenGL -framework AppKit -lm
	MLX_DIR = minilibx_mms_20200219
	DYN_LIB = libmlx.dylib
endif

_OBJ = cub3d.o image_utils.o save_bitmap.o \
	   parse.o boundary_fill.o initialize.o sprites.o hooks.o \
	   utils.o move_player.o raycast.o quit.o check_args.o \
	   project_walls.o project_walls_utils.o raycast_horizontal.o \
	   raycast_vertical.o parse_utils.o parse_grid.o save_grid.o \
	   parse_resolution.o parse_color.o parse_texture.o
OBJ := $(patsubst %, $(OBJ_DIR)/%, $(_OBJ))

_OBJ_BONUS = cub3d_bonus.o image_utils_bonus.o save_bitmap_bonus.o \
	   		parse_bonus.o boundary_fill_bonus.o initialize_bonus.o \
			sprites_bonus.o hooks_bonus.o utils_bonus.o minimap_bonus.o \
			move_player_bonus.o raycast_bonus.o quit_bonus.o check_args_bonus.o \
	   		project_walls_bonus.o project_walls_utils_bonus.o \
			raycast_horizontal_bonus.o raycast_vertical_bonus.o \
			parse_utils_bonus.o parse_grid_bonus.o save_grid_bonus.o \
	   		parse_resolution_bonus.o parse_color_bonus.o parse_texture_bonus.o
OBJ_BONUS := $(patsubst %, $(OBJ_DIR_BONUS)/%, $(_OBJ_BONUS))

_DEPS = cub3d.h libft.h
DEPS := $(patsubst %, $(INC_DIR)/%, $(_DEPS))

_DEPS_BONUS = cub3d_bonus.h libft.h
DEPS_BONUS := $(patsubst %, $(INC_DIR_BONUS)/%, $(_DEPS_BONUS))

.PHONY: all
all: $(NAME) $(NAME_BONUS)

.PHONY: bonus
bonus: $(NAME_BONUS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) $(OFLAGS) $@ $<

$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c $(DEPS_BONUS)
	$(CC) $(CFLAGS) $(OFLAGS) $@ $<

$(OBJ): | $(OBJ_DIR)

$(OBJ_BONUS): | $(OBJ_DIR_BONUS)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR_BONUS):
	mkdir $(OBJ_DIR_BONUS)

$(NAME): $(OBJ)
	make -C $(LIB_DIR)/$(MLX_DIR) 2>/dev/null
ifeq ($(UNAME),Darwin)
	cp $(LIB_DIR)/$(MLX_DIR)/$(DYN_LIB) .
endif
	make -C $(LIB_DIR)/$(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -I/$(INC_DIR) -L$(LIB_DIR)/$(MLX_DIR) -L$(LIB_DIR)/$(LIBFT_DIR) $(LFLAGS)

$(NAME_BONUS): $(OBJ_BONUS)
	make -C $(LIB_DIR)/$(MLX_DIR) 2>/dev/null
ifeq ($(UNAME),Darwin)
	cp $(LIB_DIR)/$(MLX_DIR)/$(DYN_LIB) .
endif
	make -C $(LIB_DIR)/$(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJ_BONUS) -I/$(INC_DIR_BONUS) -L$(LIB_DIR)/$(MLX_DIR) -L$(LIB_DIR)/$(LIBFT_DIR) $(LFLAGS)

.PHONY: clean
clean:
	make -C $(LIB_DIR)/$(LIBFT_DIR) fclean
	make -C $(LIB_DIR)/$(MLX_DIR) clean
	$(RMF) $(OBJ_DIR)
	$(RMF) $(OBJ_DIR_BONUS)
	$(RM) $(wildcard *.bmp)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)
ifeq ($(UNAME),Darwin)
	$(RM) $(DYN_LIB)
endif

.PHONY: re
re: fclean all bonus
