/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 03:14:14 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/05 21:01:07 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_quote(unsigned int c)
{
	return (c == '\"' || c == '\'');
}

int	is_str_quoted(char *str)
{
	int	len;

	if (str == NULL)
		return (0);
	len = ft_strlen (str);
	return (is_quote(str[0]) && is_quote(str[len - 1]));
}

void	sh_ex_removeenv(t_shell_s *shell, char *key)
{
	int		i;
	int		j;
	char	**envp;
	// char	**old_envp;

	if (sh_ex_searchenvvar(shell, key) != NULL)
	{
		shell->envp.env_size--;
		envp = malloc (sizeof(char *) * (shell->envp.env_size + 1));
		if (!envp)
			return ;
		i = 0;
		j = 0;
		while (shell->envp.envp_chain[i] != NULL)
		{
			if (ft_strncmp(key, shell->envp.envp_chain[i], ft_strlen(key)) == 0)
			{
				i++;
				continue ;
			}
			else
				envp[j++] = shell->envp.envp_chain[i++];
		}
		envp[j] = NULL;
		// old_envp = shell->envp.envp;
		shell->envp.envp_chain = sh_ex_get_envp_chain(shell);
		// sh_ex_free_arr(old_envp);
	}
}

int	sh_ex_unset(t_shell_s *shell, char **var_names)
{
	int	i;

	if (*(var_names) == NULL)
		return (0);
	i = 0;
	while (var_names[i] != NULL)
	{
		printf("hello\n");
		sh_ex_removeenv(shell, var_names[i]);
		i++;
	}
	return (0);
}
