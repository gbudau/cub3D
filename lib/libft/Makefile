# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbudau <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/11 00:42:18 by gbudau            #+#    #+#              #
#    Updated: 2020/07/01 19:58:09 by gbudau           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
COMPILE.c = $(CC) $(CFLAGS) -c
OUTPUT_OPTION = -o $@
OBJ = $(subst .c,.o,$(wildcard *.c))
AR = ar rcs
   

.PHONY: all
all: $(NAME)

%.o: %.c
	$(COMPILE.c) $< $(OUTPUT_OPTION)

$(NAME): $(OBJ) 
	$(AR) $@ $^

.PHONY: clean
clean:
	$(RM) $(OBJ)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all
