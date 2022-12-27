/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_env_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 06:33:52 by yoyohann          #+#    #+#             */
/*   Updated: 2022/12/23 06:51:31 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sh_ex_envlen(t_shell_s *shell)
{
	int	i;

	i = 0;
	while (shell->envp.envp[i])
		i++;
	shell->envp.env_size = i;
}

char	*sh_ex_searchenvvar(t_shell_s *shell, char *key)
{
	int	i;
	// int	len;

	// len = ft_strlen (key);
	i = 0;
	while (shell->envp.key[i])
	{
		if (ft_strcmp (shell->envp.key[i], key) == 0)
			return (shell->envp.value[i]);
		i++;
	}
	return (NULL);
}

void	sh_ex_memkeyval(t_shell_s *shell)
{
	shell->envp.key = malloc (sizeof(char *) * (shell->envp.env_size + 1));
	if (!shell->envp.key)
		exit (EXIT_FAILURE);
	shell->envp.value = malloc (sizeof(char *) * (shell->envp.env_size + 1));
	if (!shell->envp.value)
		exit (EXIT_FAILURE);
}

void	sh_ex_createenvp(t_shell_s *shell, char **envp)
{
	int		i;
	char	**temp_env;

	shell->envp.envp = envp;
	sh_ex_envlen (shell);
	sh_ex_memkeyval (shell);
	i = 0;
	while (shell->envp.envp[i])
	{
		temp_env = ft_split (shell->envp.envp[i], '=');
		shell->envp.key[i] = ft_strdup (temp_env[0]);
		if (temp_env[1])
			shell->envp.value[i] = ft_strdup (temp_env[1]);
		else
			shell->envp.value[i] = ft_strdup ("");
		i++;
	}
	shell->envp.key[i] = NULL;
	shell->envp.value[i] = NULL;
}
