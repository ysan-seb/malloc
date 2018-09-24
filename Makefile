# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yann <yann@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/17 07:19:36 by ysan-seb          #+#    #+#              #
#    Updated: 2018/09/24 15:32:30 by ysan-seb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# google : -iquote 

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

LN = libft_malloc.so

SRC_PATH = src/

LIB_PATH = lib/

SRCS =	$(SRC_PATH)malloc.c \
		$(SRC_PATH)ft_malloc.c \
		$(SRC_PATH)malloc_tiny.c \
		$(SRC_PATH)malloc_small.c \
		$(SRC_PATH)malloc_large.c \
		$(SRC_PATH)free.c \
		$(SRC_PATH)ft_free.c \
		$(SRC_PATH)free_tiny.c \
		$(SRC_PATH)free_small.c \
		$(SRC_PATH)free_large.c \
		$(SRC_PATH)realloc.c \
		$(SRC_PATH)ft_realloc.c \
		$(SRC_PATH)reallocf.c \
		$(SRC_PATH)ft_reallocf.c \
		$(SRC_PATH)calloc.c \
		$(SRC_PATH)ft_calloc.c \
		$(SRC_PATH)show_alloc_mem.c \
		$(SRC_PATH)ft_show_alloc_mem.c \
		$(SRC_PATH)show_graph_mem.c \
		$(SRC_PATH)defragmentation.c \
		$(SRC_PATH)get_ptr.c \
		$(SRC_PATH)environ.c \
		$(SRC_PATH)malloc_print.c \
		$(SRC_PATH)zones_is_filled.c \
		$(SRC_PATH)align.c \
		$(LIB_PATH)ft_memcpy.c \
		$(LIB_PATH)ft_memset.c \
		$(LIB_PATH)ft_putchar.c \
		$(LIB_PATH)ft_putstr.c \
		$(LIB_PATH)ft_strlen.c \
		$(LIB_PATH)ft_putnbr.c \
		$(LIB_PATH)ft_itoa_base.c \

OBJS = $(SRCS:.c=.o)

CC = gcc

FLAGS = -Wall -Werror -Wextra

DEBUG = -g -fsanatize=address

HEADER = -I./inc

LIBFT = ./libft/libft.a

RM = rm -rf

all	: $(NAME)

$(NAME):$(OBJS)
	$(CC) $(FLAGS) -g -o $(NAME) -shared  $(OBJS) $(HEADER)
	rm -f $(LN)
	ln -s $@ $(LN)

%.o: %.c inc/malloc.h
	gcc $(FLAGS) -g -o $@ -c  $< $(HEADER)

clean	:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LN)

re	:	fclean
	make

.PHONY: all lib clean fclean re
