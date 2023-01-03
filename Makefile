# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/02 13:52:30 by jyao              #+#    #+#              #
#    Updated: 2023/01/03 20:00:10 by jyao             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*- Makefile [minishell] -*-

NAME := minishell

READLINE_TMP := readline_tmp_file
READLINE_DIR = -L$(shell head -n 1 $(READLINE_TMP))/lib
READLINE_INC = -I$(shell head -n 1 $(READLINE_TMP))/include
READLINE_LIB := -lreadline
LIBFTDIR := ./libft
LIBFT = -L$(LIBFTDIR) -lft
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
	$(EXECDIR_NAME)sh_ex_env			$(EXECDIR_NAME)sh_ex_exec_extra		$(EXECDIR_NAME)sh_ex_exec_utils	\
	$(EXECDIR_NAME)sh_ex_cd				$(EXECDIR_NAME)sh_ex_export			$(EXECDIR_NAME)sh_ex_pwd	\
	$(EXECDIR_NAME)sh_ex_exit			$(EXECDIR_NAME)sh_ex_quote_utils	$(EXECDIR_NAME)sh_ex_redirect	\
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

$(OBJSDIR)%.o : $(SRCSDIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(READLINE_INC)

all: $(NAME)

$(NAME): $(READLINE_TMP) $(LIBS) $(OBJSDIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBFT) $(READLINE_DIR) $(READLINE_LIB)

$(LIBS):
	make -C $(LIBFTDIR) all

$(OBJSDIR):
	mkdir -p $@
	mkdir -p $(OBJSDIR)$(EXECDIR_NAME)
	mkdir -p $(OBJSDIR)$(PARSDIR_NAME)

$(READLINE_TMP):
	find / -maxdepth 7 -path "*/readline" 2> /dev/null | head -n 1 > $(READLINE_TMP)

clean:
	make -C $(LIBFTDIR) clean
	rm -rf $(OBJSDIR)
	rm -f $(READLINE_TMP)

fclean: clean
	make -C $(LIBFTDIR) fclean
	rm -rf $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re
