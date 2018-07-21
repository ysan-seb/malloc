# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/17 07:19:36 by ysan-seb          #+#    #+#              #
#    Updated: 2018/07/14 16:23:39 by ysan-seb         ###   ########.fr        #
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
		free.c \
		malloc.c \
		realloc.c \
		show_alloc_mem.c \
		)

#SRCS = $(SRC_PATH)main.c \
#	   $(SRC_PATH)free.c \
#	   $(SRC_PATH)malloc.c \
#	   $(SRC_PATH)realloc.c \
#	   $(SRC_PATH)show_alloc_mem.c

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra -O2 -fPIC -g

DEBUG = -g -fsanatize=address

HEADER = -I./inc

LIBFT = ./libft/libft.a

RM = rm -rf

all	: $(NAME)

$(NAME):$(OBJS)
	$(CC) $(FLAGS) -o $(NAME) -shared $(OBJS) $(HEADER)
	rm -f $(LN)
	ln -s $@ $(LN)

%.o: %.c inc/malloc.h
	gcc $(FLAGS) -c -o $@ -c $< -I./inc 


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
