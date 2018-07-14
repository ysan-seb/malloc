# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/17 07:19:36 by ysan-seb          #+#    #+#              #
#    Updated: 2017/12/27 15:41:50 by ysan-seb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# google : -iquote 

NAME	=	libft_mallo_$(HOSTTYPE).so

SRC_PATH = src/

SRCS 	= 	$(SRC_PATH)main.c \
			$(SRC_PATH)free.c \
			$(SRC_PATH)malloc.c \
			$(SRC_PATH)realloc.c \
			$(SRC_PATH)show_alloc_mem.c

OBJS = $(SRCS:.c=.o)

CC	=	gcc

CFLAGS	= -Wall -Werror -Wextra 

DEBUG = -g -fsanatize=address

HEADER = -I./

LIBFT = ./libft/libft.a

RM	=	rm -rf

all	: $(NAME)

$(NAME)	:	$(OBJS) 
	$(CC) -o $(NAME) -shared $(OBJS) $(HEADER) 

%.o: %.c inc/malloc.h
	gcc -c -Wall -Wextra -Werror -o $@ -c $< -I./inc 

clean	:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re	:	fclean
	make

.PHONY: all lib clean fclean re
