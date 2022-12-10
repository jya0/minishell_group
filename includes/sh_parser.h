/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:08:26 by jyao              #+#    #+#             */
/*   Updated: 2022/12/10 14:29:49 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_PARSER_H
# define SH_PARSER_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>


/*the members of this enum matches with 
**the members of the struct in the same order!*/
typedef enum e_ast_data_type {
	DT_NULL = -1,
	DT_LONGS,
	DT_LONGU,
	DT_CHAR_PTR,
	DT_WILD_PTR
}	t_ast_data_type;

typedef union u_ast_data {
	ssize_t			long_s;
	size_t			long_u;
	char			*str_ptr;
	void			*wild_ptr;
}	t_ast_data;

typedef enum e_ast_node_type {
	NT_NULL = -1,
	NT_TERM,
	NT_NON_TERM
}	t_ast_node_type;

typedef struct s_ast_node {
	t_ast_node_type		node_type;
	t_ast_data_type		data_type;
	t_ast_data			data;
	struct s_ast_node	*child_l;
	struct s_ast_node	*child_r;
}	t_ast_node;


#endif