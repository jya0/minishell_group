/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 08:26:01 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/11 15:33:28 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	change_env_var(t_shell_s *shell, char *key, char *value)
{
	int		index;
	char	*old_value;

	old_value = NULL;
	index = 0;
	while (shell->envp.vars[index].key != NULL)
	{
		if (ft_strcmp(shell->envp.vars[index].key, key) == 0)
			break ;
		index++;
	}
	if (shell->envp.vars[index].key != NULL)
	{
		old_value = shell->envp.vars[index].val;
		shell->envp.vars[index].val = value;
		free(old_value);
	}
	else
		free(value);
}

static void	change_pwd(t_shell_s *shell)
{
	char	*newdir;

	newdir = sh_ex_cwd();
	if (newdir)
		change_env_var(shell, "PWD", newdir);
}

static void	change_old_pwd(t_shell_s *shell)
{
	char	*pwd_val;

	pwd_val = sh_ex_searchenvvar(shell, "PWD");
	if (pwd_val != NULL)
		change_env_var(shell, "OLDPWD", ft_strdup(pwd_val));
	else
		change_env_var(shell, "OLDPWD", ft_strdup("\0"));
}

static void	calling_system_cd(t_shell_s *shell, char *dir_path)
{
	if (chdir(dir_path) == 0)
		change_pwd(shell);
	else
	{
		shell->exit_info.exit_code = EXT_CD_ERR;
		ft_putstr_fd(\
		sh_get_error_msg(shell->exit_info.exit_code), STDERR_FILENO);
	}
}

int	sh_ex_cd(t_shell_s *shell, t_commands *command)
{
	char	*home_dir;

	home_dir = sh_ex_searchenvvar(shell, "HOME");
	change_old_pwd(shell);
	if (*(command->cmd_args))
		calling_system_cd(shell, command->cmd_args[0]);
	else if (home_dir == NULL)
	{
		ft_putstr_fd("HOME NOT SET ERROR!\n", STDERR_FILENO);
		shell->exit_info.exit_code = 1;
	}
	else if (*home_dir != '\0')
		calling_system_cd(shell, home_dir);
	return (shell->exit_info.exit_code);
}
