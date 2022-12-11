/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:37:03 by jyao              #+#    #+#             */
/*   Updated: 2022/12/11 16:16:40 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*why do we need this when we already have ft_split????
**because ft_split only takes one delim char and moreover this strtok
implementation is in my opinion cleaner*/

/*frees mem allocated members and the token itself*/
void	sh_ps_token_free(t_token *token)
{
	if (token == NULL)
		return ;
	if (token->str == NULL)
		return ;
	free(token->str);
	free(token);
}

/*static function to simplify sh_ps_token*/
static t_token	*get_next_tok(const char **buf_stored, const char *delim)
{
	const char			*buf_tmp;
	unsigned int		start;
	unsigned int		end;
	t_token				*token;

	buf_tmp = *buf_stored;
	start = 0;
	while (buf_tmp[start] != '\0' && ft_strrchr(delim, buf_tmp[start]) != NULL)
		start++;
	if (buf_tmp[start] == '\0')
		return (NULL);
	end = start;
	while (buf_tmp[end] != '\0' && ft_strrchr(delim, buf_tmp[end]) == NULL)
		end++;
	if (buf_tmp[end] == '\0')
		*buf_stored = NULL;
	else
		*buf_stored = &buf_tmp[end];
	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->str_len = end - start;
	token->str = ft_substr(buf_tmp, start, token->str_len);
	return (token);
}

/*Gets the input from readline, then returns a token each time it is called!*/
t_token	*sh_ps_token(const char *buf_src, const char *delim)
{
	static const char	*buf_stored;
	t_token				*token;

	if (delim == NULL || (buf_src == NULL && buf_stored == NULL))
		return (NULL);
	else if (buf_stored == NULL && buf_src != NULL)
		buf_stored = buf_src;
	token = get_next_tok(&buf_stored, delim);
	return (token);
}

/*================Already tested for memory leaks!==================*/
/*gcc -Wall -Wextra -Werror sh_ps_token.c -L../../libft -lft*/
// /*
int	main(int argc, char	*argv[])
{
	t_token	*tok;

	if (argc == 1)
		return (0);
	tok = sh_ps_token(argv[1], TOK_DELIM);
	while (tok != NULL)
	{
		printf("%s$ %d\n", tok->str, tok->str_len);
		sh_ps_token_free(tok);
		tok = sh_ps_token(NULL, TOK_DELIM);
	}
	tok = sh_ps_token(NULL, TOK_DELIM);
	printf("===NULL TEST==\n");
	if (tok == NULL)
		printf("NULL\n");
	tok = sh_ps_token(NULL, TOK_DELIM);
	if (tok == NULL)
		printf("NULL\n");
	return (0);
}
// */
