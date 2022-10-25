# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/25 17:44:06 by jyao              #+#    #+#              #
#    Updated: 2022/10/25 19:41:05 by jyao             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*- Makefile [minishell] -*-

NAME := minishell

INCLUDES = -I./includes/ -I$(LIBFTDIR)

HEADERS = $(INCLUDES)minishell.h $(LIBFTHEADER)

LIBFTDIR = ./srcs/libft/
LIBFTHEADER = $(LIBFT)libft.h
LIBS = $(LIBFTDIR)/libft.a

CC := gcc

CFLAGS := -Wall -Wextra -Werror -g

SRCSDIR := ./srcs/

SRCSLIST = ./environment/*	\
	./executor/*		\
	./parser/*

SRCS = $(addprefix $(SRCSDIR), $(SRCSLIST))

OBJSDIR := ./objsdir/

OBJS = $(addprefix $(OBJSDIR)/, $(addsuffix .o , $(SRCS)))

all: $(NAME)

$(NAME): $(HEADERS) $(LIBS) $(OBJSDIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@

$(LIBS):
	make -C $(LIBFTDIR) all

$(OBJSDIR):
	mkdir -p $@

$(OBJDIR)/%.o : $(SRCS)%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

clean:
	make -C $(LIBFTDIR) clean
	rm -rf $(OBJSDIR)

fclean: clean
	make -C $(LIBFTDIR) fclean
	rm -rf $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re