/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 03:14:14 by yoyohann          #+#    #+#             */
/*   Updated: 2022/12/23 08:16:56 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sh_ex_removeenv(t_shell_s *shell, char *key)
{
	int		i;
	int		j;
	char	**envp;
	int		size;
	char	*str;

	if (sh_ex_searchenvvar (shell, key) != NULL)
	{
		shell->envp.env_size--;
		envp = malloc (sizeof(char *) * (shell->envp.env_size + 1));
		if (!envp)
			return ;
		i = 0;
		j = 0;
		while (shell->envp.envp[i])
		{
			if (ft_strncmp(key, shell->envp.envp[i], ft_strlen (key)) == 0)
			{
				i++;
				continue ;
			}
			else
				envp[j++] = shell->envp.envp[i++];
		}
		envp[j] = NULL;
		shell->envp.envp = NULL;
		shell->envp.envp = envp;
	}
}

void	sh_ex_unset(t_shell_s *shell)
{
	char	**tmp_str;
	char	*tmp;
	char	*str;

	tmp_str = ft_split (shell->cmd_line, ' ');
	if (tmp_str[1] != NULL)
	{
		str = sh_ps_removequote (tmp_str[1]);
		sh_ex_removeenv (shell, str);
		sh_ex_createenvp (shell, shell->envp.envp);
	}
}
