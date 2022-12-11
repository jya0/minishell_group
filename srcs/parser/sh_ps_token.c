/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:37:03 by jyao              #+#    #+#             */
/*   Updated: 2022/12/11 12:48:37 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*why do we need this when we already have ft_split????
**because ft_split only takes one delim char and moreover this strtok
implementation is in my opinion cleaner*/

static char	*get_next_tok(const char **buf_stored, const char *delim)
{
	const char			*buf_tmp;
	unsigned int		start;
	unsigned int		end;

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
	return (ft_substr(buf_tmp, start, end - start));
}

/*Gets the input from readline, then returns a token string each time it is called!*/
char	*sh_ps_token(const char *buf_src, const char *delim)
{
	static const char	*buf_stored;
	char				*tok;

	if (delim == NULL || (buf_src == NULL && buf_stored == NULL))
		return (NULL);
	else if (buf_stored == NULL && buf_src != NULL)
		buf_stored = buf_src;
	tok = get_next_tok(&buf_stored, delim);
	// if (buf_stored)
	// 	printf("char = %c\n", *buf_stored);
	return (tok);
}


/*================Already tested for memory leaks!==================*/
// /*
int	main(int argc, char	*argv[])
{
	char	*tok;

	if (argc == 1)
		return (0);
	tok = sh_ps_token(argv[1], TOK_DELIM);
	while (tok != NULL)
	{
		printf("%s %d\n", tok, ft_strlen(tok));
		free(tok);
		// sleep(5);
		tok = sh_ps_token(NULL, TOK_DELIM);
	}
	return (0);
}
// */

