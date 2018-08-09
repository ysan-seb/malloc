# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yann <yann@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/17 07:19:36 by ysan-seb          #+#    #+#              #
#    Updated: 2018/08/07 21:54:35 by yann             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# google : -iquote 

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

LN = libft_malloc.so

SRC_PATH = src/

SRCS =	$(addprefix $(SRC_PATH), \
		malloc.c \
		malloc_tiny.c \
		malloc_small.c \
		malloc_large.c \
		free.c \
		free_tiny.c \
		free_small.c \
		free_large.c \
		realloc.c \
		get_ptr.c \
		show_alloc_mem.c \
		lib.c \
		)

#SRCS = $(SRC_PATH)main.c \
#	   $(SRC_PATH)free.c \
#	   $(SRC_PATH)malloc.c \
#	   $(SRC_PATH)realloc.c \
#	   $(SRC_PATH)show_alloc_mem.c

OBJS = $(SRCS:.c=.o)

CC = gcc

FLAGS = -Wall -Werror -Wextra -Wpadded

DEBUG = -g -fsanatize=address

HEADER = -I./inc

LIBFT = ./libft/libft.a

RM = rm -rf

all	: $(NAME)

$(NAME):$(OBJS)
	$(CC) $(FLAGS) -g -o $(NAME) -shared $(OBJS) $(HEADER)
	rm -f $(LN)
	ln -s $@ $(LN)

%.o: %.c inc/malloc.h
	gcc $(FLAGS) -g -c -o $@ -c $< $(HEADER)


#$(NAME): $(SRC)
#	$(CC) $(FLAGS) -o $(NAME) -shared $(OBJS) $(HEADER)
#	ln -s $@ $(LN)

#%.o: %.c inc/malloc.h
#	gcc -c $(FLAGS) -o $@ -c $< -I./inc 

clean	:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LN)

re	:	fclean
	make

.PHONY: all lib clean fclean re
