/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 08:26:01 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/09 23:32:55 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	sh_ex_searchenvindex(t_shell_s *shell, char *key)
{
	int	i;
	int	len;

	len = ft_strlen (key);
	i = 0;
	while (shell->envp.vars[i].key != NULL)
	{
		if (ft_strncmp (shell->envp.vars[i].key, key, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static void	sh_ex_changeenv(t_shell_s *shell, char *key, char *value)
{
	int		index;
	char	*old_value;

	old_value = NULL;
	index = sh_ex_searchenvindex(shell, key);
	if (index >= 0)
	{
		old_value = shell->envp.vars[index].val;
		shell->envp.vars[index].val = value;
		free(old_value);
	}
}

static void	change_old_pwd(t_shell_s *shell)
{
	char	*pwd_val;

	pwd_val = sh_ex_searchenvvar(shell, "PWD");
	if (pwd_val != NULL)
		sh_ex_changeenv(shell, "OLDPWD", ft_strdup(pwd_val));
	else
		sh_ex_changeenv(shell, "OLDPWD", ft_strdup("\0"));
}

int	sh_ex_cd(t_shell_s *shell, t_commands *command)
{
	change_old_pwd(shell);
	if (*(command->cmd_args))
	{
		if (chdir(command->cmd_args[0]) == 0)
			sh_ex_changepwd(shell);
		else
		{
			shell->exit_info.exit_code = EXT_CD_ERR;
			ft_putstr_fd(\
			sh_get_error_msg(shell->exit_info.exit_code), STDERR_FILENO);
		}
	}
	else
	{
		if (sh_ex_searchenvvar(shell, "HOME"))
		{
			chdir(shell->home);
			shell->cwd = shell->home;
			sh_ex_changepwd(shell);
		}
	}
	return (0);
}

void	sh_ex_changepwd(t_shell_s *shell)
{
	char	*newdir;

	newdir = sh_ex_cwd();
	if (newdir)
		sh_ex_changeenv(shell, "PWD", newdir);
}
