# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/02 13:52:30 by jyao              #+#    #+#              #
#    Updated: 2023/01/02 15:24:01 by jyao             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*- Makefile [minishell] -*-

NAME := minishell

READLINE_DIR = $(shell brew --prefix readline)
READLINE_LIB = -lreadline -lhistory -L$(READLINE_DIR)/lib
LIBFTDIR = ./libft/
LIBFTHEADER = $(LIBFT)libft.h
LIBS = $(LIBFTDIR)/libft.a

# INCLUDES = -I./includes/ -I$(LIBFTDIR)
HEADERS = minishell.h $(LIBFTHEADER)

CC := gcc
CFLAGS := -Wall -Wextra -Werror -g3

SRCSDIR := ./srcs/
EXECDIR_NAME := executor/
PARSDIR_NAME := parser/
FILES =	$(EXECDIR_NAME)main \
	$(EXECDIR_NAME)sh_ex_builtin		$(EXECDIR_NAME)sh_ex_bindir			$(EXECDIR_NAME)sh_ex_quote	\
	$(EXECDIR_NAME)sh_ex_signal			$(EXECDIR_NAME)sh_ex_shellinit		$(EXECDIR_NAME)sh_ex_utils	\
	$(EXECDIR_NAME)sh_ex_env_utils		$(EXECDIR_NAME)sh_ex_echo			$(EXECDIR_NAME)sh_ex_unset	\
	$(EXECDIR_NAME)sh_ex_cd				$(EXECDIR_NAME)sh_ex_export			$(EXECDIR_NAME)sh_ex_pwd	\
	$(EXECDIR_NAME)sh_ex_exit			$(EXECDIR_NAME)sh_ex_quote_utils	$(EXECDIR_NAME)sh_ex_executor	\
	$(EXECDIR_NAME)extra	\
	$(PARSDIR_NAME)sh_ps_parser_cmds	$(PARSDIR_NAME)sh_ps_parser_cmds_getters	\
	$(PARSDIR_NAME)sh_ps_parser_cmds_free	\
	$(PARSDIR_NAME)sh_ps_lexer			$(PARSDIR_NAME)sh_ps_lexer_words	$(PARSDIR_NAME)sh_ps_lexer_add_missing	\
	$(PARSDIR_NAME)sh_ps_lexer_expand_quotes	\
	$(PARSDIR_NAME)sh_ps_parser			$(PARSDIR_NAME)sh_ps_lexer_check_error	\
	$(PARSDIR_NAME)sh_ps_heredoc	\

SRCS = $(addprefix $(SRCSDIR), $(addsuffix .c, $(FILES)))

OBJSDIR := ./objsdir/
OBJS = $(addprefix $(OBJSDIR), $(addsuffix .o, $(FILES)))

$(OBJSDIR)%.o : $(SRCS)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(LIBS) $(OBJSDIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ -L$(LIBFTDIR) -lft $(READLINE_LIB)

$(LIBS):
	make -C $(LIBFTDIR) all

$(OBJSDIR):
	mkdir -p $@
	mkdir -p $(OBJSDIR)$(EXECDIR_NAME)
	mkdir -p $(OBJSDIR)$(PARSDIR_NAME)

clean:
	make -C $(LIBFTDIR) clean
	rm -rf $(OBJSDIR)

fclean: clean
	make -C $(LIBFTDIR) fclean
	rm -rf $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re
