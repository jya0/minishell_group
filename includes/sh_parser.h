/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:08:26 by jyao              #+#    #+#             */
/*   Updated: 2022/12/12 14:55:20 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_PARSER_H
# define SH_PARSER_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

/*==================DEFINING CONSTANTS======================*/

# define TOK_DELIM	" \n\t\v\f\r"

/*==================SECTION FOR TOKENIZING===============*/

typedef struct s_token {
	int		str_len;
	char	*str;
}	t_token;

/*=======SECTION FOR ABSTRACT SYNTAX TREE==============*/

/*This is resposible to see if the t_data of the node 
**needs further expansion or not*/

enum e_node_type {
	NT_NULL = -1,
	NT_TERM,
	NT_QUOTE_S,
	NT_QUOTE_D,
	NT_DOLLAR,
	NT_CMD,
	NT_CMD_ARGS,
	NT_CMD_FLAG,
};

/*Once the ast t_node_type of the node is marked as NT_TERM
**it should be next to mark the type of the terminal in t_term_type*/
enum e_term_type {
	TT_NULL = -1,
	TT_PIPE,
	TT_REDIR_IN,
	TT_REDIR_OUT,
	TT_APPND_IN,
	TT_APPND_OUT
};

/*the members of this enum helps to chose the members of the struct t_data!
**Add more members as fit!*/
enum e_data_type {
	DT_NULL = -1,
	DT_CHAR,
	DT_LONG_S,
	DT_LONG_U,
	DT_STR,
	DT_STR_ARR,
	DT_LST_LIBFT
};

/*t_data should be expanded from the tokens got from the tokenizing functions
**Data depends on t_term_type*/
union u_data_content {
	char			c;
	ssize_t			long_s;
	size_t			long_u;
	void			*ptr_w_1d;
	void			**ptr_w_2d;
};

typedef struct s_data {
	enum e_data_type		data_type;
	union u_data_content	data_content;
}	t_data;

/*the building block of an abstract syntax tree!*/
typedef struct s_ast_node {
	enum e_term_type	term_type;
	// enum e_node_type	node_type;
	t_data				data;
	// struct s_ast_node	*parent;
	struct s_ast_node	*child_l;
	struct s_ast_node	*child_r;
}	t_ast_node;

typedef struct s_ast {
	t_ast_node	*root;
	t_ast_node	*last_non_term;
}	t_ast;

#endif
