SRC = ./srcs/main.c ./libft/ft_split.c ./libft/ft_strdup.c ./libft/ft_strlen.c \
		./libft/ft_strncmp.c ./libft/ft_strjoin.c ./srcs/sh_ex_executor.c \
		./srcs/ft_splitset.c 	./srcs/sh_ex_builtin.c ./libft/ft_substr.c  \
		./srcs/sh_ex_bindir.c ./srcs/sh_ex_quote.c ./srcs/sh_ex_signal.c \
		./libft/ft_strcmp.c
all:
	gcc $(SRC) -o shell -lreadline