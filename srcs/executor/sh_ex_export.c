/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:36:57 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/01 20:05:06 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sh_ex_addenv(t_shell_s *shell, char *str)
{
	int		i;
	char	**envp;

	envp = malloc (sizeof(char *) * (shell->envp.env_size + 2));
	if (!envp)
		exit (EXIT_FAILURE);
	i = 0;
	while (shell->envp.envp[i])
	{
		envp[i] = shell->envp.envp[i];
		i++;
	}
	if (str)
	{
		envp[i++] = ft_strdup (str);
		envp[i] = NULL;
	}
	else
		envp[i] = NULL;
	shell->envp.envp = NULL;
	shell->envp.envp = envp;
}

int	sh_ex_export(t_shell_s *shell)
{
	char	*str;
	char	**tmp_str;
	char	**tmp_env;

	str = NULL;
	tmp_str = ft_split (shell->cmd_line, ' ');
	if (tmp_str[1] == NULL)
	{
		sh_ex_viewenvp (shell);
		return (0);
	}
	else
	{
		str = sh_ps_removequote (tmp_str[1]);
		tmp_env = ft_split (str, '=');
		if (sh_ex_searchenvvar (shell, tmp_env[0]) == NULL)
		{
			shell->envp.env_size++;
			sh_ex_addenv (shell, str);
			sh_ex_createenvp (shell, shell->envp.envp);
		}
	}
	free (str);
	return (0);
}

int	sh_ex_searchenvindex(t_shell_s *shell, char *key)
{
	int	i;
	int	len;

	len = ft_strlen (key);
	i = 0;
	while (shell->envp.key[i])
	{
		if (ft_strncmp (shell->envp.key[i], key, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	sh_ex_changeenv(t_shell_s *shell, char *key, char *value)
{
	int	index;

	index = sh_ex_searchenvindex (shell, key);
	if (index)
		shell->envp.value[index] = value;
}
