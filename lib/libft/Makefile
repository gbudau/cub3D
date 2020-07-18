# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbudau <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/11 00:42:18 by gbudau            #+#    #+#              #
#    Updated: 2020/07/16 16:43:33 by gbudau           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
COMPILE.c = $(CC) $(CFLAGS) -c
OUTPUT_OPTION = -o $@
OBJ = ft_atoi.o ft_bzero.o ft_calloc.o ft_lstrev.o \
	  ft_isalnum.o ft_isalpha.o ft_isascii.o \
	  ft_isdigit.o ft_isprint.o ft_isspace.o \
	  ft_itoa.o ft_lstadd_back.o ft_lstadd_front.o \
	  ft_lstclear.o ft_lstdelone.o ft_lstiter.o \
	  ft_lstlast.o ft_lstmap.o ft_lstnew.o ft_lstsize.o \
	  ft_memccpy.o ft_memchr.o ft_memcmp.o ft_memcpy.o \
	  ft_memmove.o ft_memset.o ft_putchar_fd.o \
	  ft_putendl_fd.o ft_putnbr_fd.o ft_putstr_fd.o \
	  ft_split.o ft_strchr.o ft_strcpy.o ft_strcspn.o \
	  ft_strdup.o ft_strjoin_free.o ft_strjoin.o \
	  ft_strlcat.o ft_strlcpy.o ft_strlen.o ft_strmapi.o \
	  ft_strncmp.o ft_strndup.o ft_strnstr.o ft_strrchr.o \
	  ft_strtrim.o ft_substr.o ft_tolower.o ft_toupper.o \
	  get_next_line.o ft_abs.o
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
