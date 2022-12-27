/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_quote_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 07:32:37 by yoyohann          #+#    #+#             */
/*   Updated: 2022/12/25 19:06:54 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_ps_issinglequotedarg(char *str)
{
	int	len;

	len = ft_strlen (str);
	if (str)
	{
		if (sh_ps_issinglequote (str[0]) && sh_ps_issinglequote (str[len - 1]))
			return (1);
	}
	return (0);
}

int	sh_ps_isvalidname(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && \
				c <= 'z') || (c >= '0' && c <= '9') || (c == '_'))
		return (1);
	return (0);
}

char	*sh_ps_trimspace(char *str)
{
	int		i;
	int		j;
	char	*sub_str;

	j = ft_strlen (str);
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (j >= 0 && str[j] == ' ')
		j--;
	sub_str = word_dup (str, i, j);
	return (sub_str);
}

char *word_dup(char *str, int start, int finish)
{
	char *word;
	int i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}