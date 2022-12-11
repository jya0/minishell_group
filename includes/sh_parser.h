/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:08:26 by jyao              #+#    #+#             */
/*   Updated: 2022/12/11 12:43:28 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_PARSER_H
# define SH_PARSER_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

/*==================defining constants======================*/

# define TOK_DELIM	" \n\t\v\f\r"

/*==================defining constants======================*/



/*=======SECTION FOR ABSTRACT SYNTAX TREE==============*/

/*the members of this enum matches with 
**the members of the struct in the same order!*/
typedef enum e_data_type {
	DT_NULL = -1,
	DT_LONG_S,
	DT_LONG_U,
	DT_STR,
	DT_STR_ARR
}	t_data_type;

typedef union u_data {
	ssize_t			long_s;
	size_t			long_u;
	char			*str;
	char			**str_arr;
}	t_data;

typedef enum e_node_type {
	NT_NULL = -1,
	NT_TERM,
	NT_NON_TERM
}	t_node_type;

typedef enum e_term_type {
	TT_NULL = -1,
	TT_CMD,
	TT_CMD_ARGS,
	TT_PIPE,
	TT_REDIR_L,
	TT_REDIR_R,
	TT_APPND_L,
	TT_APPND_R
}	t_term_type;

typedef struct s_ast_node {
	t_node_type			node_type;
	t_term_type			term_type;
	t_data_type			data_type;
	t_data				data;
	struct s_ast_node	*parent;
	struct s_ast_node	*child_l;
	struct s_ast_node	*child_r;
}	t_ast_node;

/*=======SECTION FOR ABSTRACT SYNTAX TREE==============*/

#endif
