NAME = shell

FILES = readline.c nextchar.c parser.c token.c execute.c  builtins.c \
		initsh.c symtab.c main.c

CC = gcc
RM = rm -f
FLAGS = -Wall -Wextra -Werror

all:
	$(CC) $(FLAGS) $(FILES) -o $(NAME)
noflag:
	$(CC) $(FILES) -o $(NAME)
clean:
	$(RM) $(NAME)