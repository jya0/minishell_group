NAME = minishell
READLINE_DIR = $(shell brew --prefix readline)

READLINE_LIB = -lreadline -lhistory -L $(READLINE_DIR)/lib

FLAG = -Wall -Wextra -Werror -g3
SRC = ./srcs/executor/main.c ./libft/ft_split.c ./libft/ft_strdup.c ./libft/ft_strlen.c \
		./libft/ft_strncmp.c ./libft/ft_strjoin.c  \
		./srcs/executor/sh_ex_builtin.c ./libft/ft_substr.c  \
		./srcs/executor/sh_ex_bindir.c ./srcs/executor/sh_ex_quote.c ./srcs/executor/sh_ex_signal.c \
		./libft/ft_strcmp.c ./srcs/executor/sh_ex_shellinit.c ./srcs/executor/sh_ex_utils.c \
		./srcs/executor/sh_ex_env_utils.c ./srcs/executor/sh_ex_echo.c ./srcs/executor/sh_ex_unset.c \
		./libft/ft_putstr_fd.c ./libft/ft_putchar_fd.c ./libft/ft_putnbr_fd.c	\
		 ./srcs/parser/sh_ps_parser_cmds.c ./srcs/parser/sh_ps_parser_cmds_getters.c \
		./srcs/parser/sh_ps_parser_cmds_free.c ./srcs/parser/sh_ps_lexer.c ./srcs/parser/sh_ps_lexer_words.c \
		./libft/ft_strrchr.c ./libft/ft_calloc.c ./libft/ft_bzero.c ./srcs/executor/sh_ex_env.c \
		./srcs/executor/sh_ex_cd.c  ./srcs/executor/sh_ex_export.c ./srcs/executor/sh_ex_pwd.c \
		./srcs/executor/sh_ex_exit.c  ./srcs/executor/sh_ex_quote_utils.c \
		./srcs/parser/sh_ps_lexer_add_missing.c ./srcs/parser/sh_ps_lexer_expand_quotes.c ./libft/ft_strlcpy.c \
		./srcs/parser/sh_ps_parser.c ./srcs/executor/sh_ex_executor.c ./srcs/executor/extra.c	\
		./srcs/parser/sh_ps_lexer_check_error.c

#	./srcs/executor/sh_ex_executor.c ./srcs/executor/ft_splitset.c ./srcs/executor/extra.c
all: 
	gcc $(READLINE_LIB) $(SRC) -g3 -o $(NAME) 
clean:
	rm $(NAME)
	rm -rf minishell.dSYM
re: clean all

leak:
	valgrind --leak-check=full ./$(NAME)
