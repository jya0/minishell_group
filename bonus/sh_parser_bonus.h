/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:08:26 by jyao              #+#    #+#             */
/*   Updated: 2023/01/11 15:15:11 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_PARSER_H
# define SH_PARSER_H

/*==================DEFINING CONSTANTS======================*/

# define DELIM_SPACES				" \n\t\v\f\r"
# define DELIM_TERMS_COMBINEABLE	"<>|&$"
# define DELIM_TERMS_ALL			"<>|&$()'\""
# define UNDERSCORE					"_"
# define D_DIGITS					"0123456789"
# define A_LOWER					"abcdefghijklmnopqrstuvwxyz"
# define A_UPPER					"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define S_D_QUOTES					"\'\""

# define BKT_STK_MAX				2048
# define HEREDOC_FILE				"/tmp/.heredoc_tmp"

typedef struct t_shell_s	t_shell_s;

enum e_term_type {
	TT_ERROR = -1,
	TT_NULL,
	TT_JUST_WORD,
	TT_VAR = '$',
	TT_QUOTE_S = '\'',
	TT_QUOTE_D = '\"',
	TT_PIPE = '|',
	TT_REDIR_IN = '<',
	TT_REDIR_OUT = '>',
	TT_APPND_IN = '<' * '<',
	TT_APPND_OUT = '>' * '>',
	TT_COND_AND = '&' * '&',
	TT_COND_OR = '|' * '|',
	TT_BKT_RND_L = '(',
	TT_BKT_RND_R = ')'
};

enum e_exit_codes {
	EXT_MALLOC_FAILURE = -255,
	EXT_HEREDOC_ERR = 256,
	EXT_QUOTES_ERR,
	EXT_REDIR_ERR,
	EXT_PIPE_ERR,
	EXT_SYNTAX_ERR,
	EXT_CMD_NOT_FOUND_ERR = 127,
	EXT_CANT_FORK_ERR,
	EXT_CD_ERR = 1,
	EXT_INVALID_KEY_ERR = 1,
	EXT_NOT_VALID_KEY_ERR,
	EXT_IN_FILE_ERR,
	EXT_OUT_FILE_ERR,
};

/*==================SECTION FOR TOKENIZING===============*/

/*
** str_end is the address of the first charater of the str, in the 
** original readline string (buf_src)
*/
typedef struct s_words {
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
	char					*redir_file;
	enum e_term_type		redir_term_type;
	struct s_redirections	*next;
}	t_redirections;

/*commands will only pipe to the next one if redirecs_out is null!*/
typedef struct s_commands {
	char				**cmd_argv;
	char				*cmd_name;
	char				**cmd_args;
	t_redirections		*redirs;
	struct s_commands	*next;
}	t_commands;

/*pipeline_return is the exit status of the last command of the pipeline!*/
typedef struct s_pipelines {
	t_words				*words;
	t_commands			*commands;
	int					pipeline_return;
	enum e_term_type	cond_term_type;
	struct s_pipelines	*next;
}	t_pipelines;

typedef struct s_conditionals {
	size_t					index;
	t_pipelines				*pipelines;
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

/*===================sh_ps_lexer.c=====================*/

t_words			*sh_ps_lexer(t_shell_s *shell, const char *buf_src, int *lexer_error_code);

/*===========sh_ps_lexer_check_error.c=============*/

int				sh_ps_lexer_check_error(t_words *head_word);

/*=============sh_ps_lexer_add_missing.c===============*/

enum e_quote_state {
	IN_NULL = -1,
	IN_QUOTE_S = TT_QUOTE_S,
	IN_QUOTE_D = TT_QUOTE_D
};

int				sh_ps_lexer_add_missing(t_shell_s *shell, t_words **head_word);

/*=============sh_ps_lexer_expand_quotes.c===============*/

void			sh_ps_lexer_expand_quotes(t_words **head_word);

/*==============sh_ps_lexer_join_connected.c================*/

int				sh_ps_lexer_join_connected(t_words	**head_word);

/*====================sh_ps_heredoc.c=====================*/

int				sh_ps_lexer_heredoc_mark_variable(t_words *head_word);

int				sh_ps_parser_heredoc(t_redirections *redirection);

/*=============sh_ps_parser.c===============*/

t_commands		*sh_ps_parser(t_shell_s *shell, char *buf_src);

/*===================sh_ps_parser_commands.c=====================*/

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

/*=================sh_get_error_message.c===================*/

char			*sh_get_error_msg(enum e_exit_codes exit_code);

#endif
