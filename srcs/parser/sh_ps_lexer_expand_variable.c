/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_lexer_expand_variable.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:38:55 by jyao              #+#    #+#             */
/*   Updated: 2023/01/13 22:27:38 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	count_env_var_value_return(char *value)
{
	size_t		i;
	size_t		j;
	int			space_allow;

	space_allow = 0;
	i = 0;
	j = 0;
	while (value[i] != '\0')
	{
		if (strchr(DELIM_SPACES, value[i]) != NULL)
		{
			if (space_allow == 1)
			{
				j++;
				space_allow = !space_allow;
			}
		}
		else
		{
			space_allow += (space_allow == 0);
			j++;
		}
		i++;
	}
	return (j);
}

static void	copy_str_with_no_extra_gap(char *dst, char *value)
{
	size_t		i;
	size_t		j;
	int			space_allow;

	space_allow = 0;
	i = 0;
	j = 0;
	while (value[i] != '\0')
	{
		if (strchr(DELIM_SPACES, value[i]) != NULL)
		{
			if (space_allow == 1)
			{
				dst[j++] = value[i];
				space_allow = !space_allow;
			}
		}
		else
		{
			space_allow += (space_allow == 0);
			dst[j++] = value[i];
		}
		i++;
	}
}

static char	*expand_env_var(t_shell_s *shell, t_words *word)
{
	char	*value;
	char	*result;
	size_t	res_len;

	value = sh_ex_searchenvvar(shell, &((word->str)[1]));
	if (value == NULL)
		return (NULL);
	res_len = count_env_var_value_return(value);
	result = (char *)ft_calloc(res_len + 1, sizeof(char));
	copy_str_with_no_extra_gap(result, value);
	if (ft_strchr(DELIM_SPACES, result[res_len - 1]) != NULL)
		result[res_len - 1] = '\0';
	return (result);
}

static t_words	*expand_variable(\
t_shell_s *shell, t_words *word, enum e_quote_state quote_state)
{
	char	*value;

	if (word == NULL)
		return (0);
	if (word->str_len <= 1 && !((word->str)[1] == '\0' \
	&& *(word->str_start + sizeof(char)) != '\0' \
	&& ft_strchr("\'\"", *(word->str_start + sizeof(char))) != NULL \
	&& quote_state == IN_NULL))
		return (word);
	if (ft_strcmp(word->str, "$?") == 0)
		value = ft_itoa(shell->exit_info.exit_code);
	else
		value = expand_env_var(shell, word);
	free(word->str);
	word->str = value;
	word->str_len = ft_strlen(word->str);
	word->term_type = TT_JUST_WORD;
	return (word);
}

t_words	*sh_ps_lexer_expand_variable(\
t_shell_s *shell, t_words *word, enum e_quote_state quote_state)
{
	if (word == NULL)
		return (NULL);
	return (expand_variable(shell, word, quote_state));
}
