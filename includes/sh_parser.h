/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:08:26 by jyao              #+#    #+#             */
/*   Updated: 2022/12/27 15:16:03 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_PARSER_H
# define SH_PARSER_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

/*==================DEFINING CONSTANTS======================*/

# define DELIM_SPACES				" \n\t\v\f\r"
# define DELIM_TERMS_COMBINEABLE	"<>|&$"
# define DELIM_TERMS_ALL			"<>|&$()'\""

# define BKT_STK_MAX				2048

enum e_term_type {
	TT_ERROR = -1,
	TT_NULL,
/*CMD part*/
	TT_JUST_WORD,
	TT_VAR = '$',
	TT_QUOTE_S = '\'',
	TT_QUOTE_D = '\"',
	TT_PIPE = '|',
	TT_REDIR_IN = '<',
	TT_REDIR_OUT = '>',
	TT_APPND_IN = '<' * '<',
	TT_APPND_OUT = '>' * '>',
/*BONUS conditionals part*/
	TT_COND_AND = '&' * '&',
	TT_COND_OR = '|' * '|',
	TT_BKT_RND_L = '(',
	TT_BKT_RND_R = ')'
};

/*==================SECTION FOR TOKENIZING===============*/

/*
** str_end is the address of the first charater of the str, in the 
** original readline string (buf_src)
*/
typedef struct s_words {
	// size_t				index;
	char				*str;
	const char			*str_start;
	size_t				str_len;
	enum e_term_type	term_type;
	struct s_words		*next;
	struct s_words		*prev;
}	t_words;

/*==================SECTION FOR PARSER====================*/

/*redirections of commands always only 
**work for the last encountered redirection!
**multiple redirections will cause default behaviour to occur for each
**until the one before the last one!
**that is if the redirection is not the last one 
** '>' will wipe the file if it exists or make it if it doesn't
** '<' && '<<' doesn't really do anything, or do they?*/
typedef struct s_redirections {
	// size_t					index;
	char					*redir_file;
	enum e_term_type		redir_term_type;
	struct s_redirections	*next;
}	t_redirections;

/*commands will only pipe to the next one if redirecs_out is null!*/
typedef struct s_commands {
	// size_t				index;
	char				**cmd_argv;
	char				*cmd_name;
	char				**cmd_args;
	t_redirections		*redirs_in;
	t_redirections		*redirs_out;
	// int					exit_code_cmd;
	struct s_commands	*next;
}	t_commands;

/*pipeline_return is the exit status of the last command of the pipeline!*/
typedef struct s_pipelines {
	// size_t				index;
	t_words				*words;
	t_commands			*commands;
	int					pipeline_return;
	enum e_term_type	cond_term_type;
	struct s_pipelines	*next;
}	t_pipelines;

typedef struct s_conditionals {
	size_t					index;
	t_pipelines				*pipelines;
	// int						conditional_return;
	struct s_conditionals	*next;
}	t_conditionals;

/*===================sh_ps_lexer_words.c=====================*/

enum e_free_option {
	FREE_DEFAULT,
	FREE_ALL
};

void			sh_ps_lexer_word_free_list(t_words	*head_word);

t_words			*sh_ps_lexer_word_add_end(\
t_words	*head_word, t_words	*word);

t_words			*sh_ps_lexer_word_add_after(t_words *word, t_words *new_word);

t_words			*sh_ps_lexer_word_del_word(\
t_words **head_word, t_words *word, enum e_free_option flag);

void			sh_ps_lexer_word_print_list(t_words *head_word);

/*===================sh_ps_lexer.c=====================*/

t_words			*sh_ps_lexer(t_shell_s *shell, const char *buf_src);

/*===========sh_ps_lexer_check_error.c=============*/

int				sh_ps_lexer_check_error(t_words *head_word);

/*=============sh_ps_lexer_add_missing.c===============*/

enum e_quote_state {
	IN_NULL = -1,
	IN_QUOTE_S = TT_QUOTE_S,
	IN_QUOTE_D = TT_QUOTE_D
};

int				sh_ps_lexer_add_missing(t_shell_s *shell, t_words *head_word);

/*=============sh_ps_lexer_expand_quotes.c===============*/

void			sh_ps_lexer_expand_quotes(t_words **head_word);

/*===================sh_ps_parser_commands.c=====================*/

enum e_pipe_error_check {
	CHECK_BEFORE,
	CHECK_AFTER
};

t_commands		*sh_ps_parser_commands(t_words	*head_word);

/*=============sh_ps_parser_cmds_getters.c===============*/

int				sh_ps_parser_get_redirs(\
t_commands *command, t_words **head_word);

int				sh_ps_parser_get_cmd_name(\
t_commands *command, t_words **head_word, t_words	**word);

int				sh_ps_parser_get_cmd_args(\
t_commands *command, t_words **head_word, t_words **word);

int				sh_ps_parser_get_cmd_argv(\
t_commands *command, t_words **head_word);

/*=============sh_ps_parser_cmds_free.c===============*/

void			sh_ps_parser_commands_free(\
t_commands *command, enum e_free_option flag);

void			sh_ps_parser_commands_free_list(\
t_commands *head_command);

/*=============sh_ps_parser.c===============*/

t_commands		*sh_ps_parser(t_shell_s *shell, char *buf_src);

// /*=======SECTION FOR ABSTRACT SYNTAX TREE==============*/

// /*DEPRECATED!!!!!!!!! FINALLY IT'S DISCOVERED THAT ASTS
// ** PRETTY BAD FOR ONLY PARSING COMMAND LINES!*/

// /*This is resposible to see if the t_data of the node 
// **needs further expansion or not*/

// enum e_node_type {
// 	NT_NULL = -1,
// 	NT_TERM,
// 	NT_QUOTE_S,
// 	NT_QUOTE_D,
// 	NT_DOLLAR,
// 	NT_CMD,
// 	NT_CMD_ARGS,
// 	NT_CMD_FLAG,
// };

// /*the members of this enum helps to chose the members of the struct t_data!
// **Add more members as fit!*/
// enum e_data_type {
// 	DT_NULL = -1,
// 	DT_CHAR,
// 	DT_LONG_S,
// 	DT_LONG_U,
// 	DT_STR,
// 	DT_STR_ARR,
// 	DT_LST_LIBFT
// };

// /*t_data should be expanded from the tokens got from the tokenizing functions
// **Data depends on t_term_type*/
// union u_data_content {
// 	char			c;
// 	ssize_t			long_s;
// 	size_t			long_u;
// 	void			*ptr_w_1d;
// 	void			**ptr_w_2d;
// };

// typedef struct s_data {
// 	enum e_data_type		data_type;
// 	union u_data_content	data_content;
// }	t_data;

// /*the building block of an abstract syntax tree!*/
// typedef struct s_ast_node {
// 	enum e_term_type	term_type;
// 	enum e_node_type	node_type;
// 	t_data				data;
// 	struct s_ast_node	*parent;
// 	struct s_ast_node	*child_l;
// 	struct s_ast_node	*child_r;
// }	t_ast_node;

// typedef struct s_ast {
// 	t_ast_node	*root;
// 	t_ast_node	*last_non_term;
// }	t_ast;

// typedef struct s_minishell {
// 	t_conditionals	*root_condition;
// }	t_minishell;

#endif
