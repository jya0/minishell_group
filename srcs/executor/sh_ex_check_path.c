/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_check_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 00:09:29 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/23 04:40:17 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*exec_path(char **path, char *cmd)
{
	int		i;
	char	*realpath;

	i = 0;
	g_shell.check = 0;
	while (path[i] != NULL)
	{
		realpath = ft_strjoin(path[i], cmd);
		if (access(realpath, F_OK) == 0)
		{
			if (access(realpath, X_OK) != 0)
			{
				g_shell.check = 2;
				break ;
			}
			sh_ex_free_arr(path);
			g_shell.check = 1;
			return (realpath);
		}
		free(realpath);
		i++;
	}
	g_shell.exit_info.exit_code = 126;
	return (NULL);
}

char	*path_var_path(t_shell_s *shell, char *cmd)
{
	char	**path;
	char	*realpath;

	path = dir_path(shell);
	if (path != NULL)
	{
		realpath = exec_path(path, cmd);
		if (realpath != NULL)
			return (realpath);
	}
	sh_ex_free_arr(path);
	return (NULL);
}

/* char	*path_var_path(t_shell_s *shell, char *cmd)
{
	char	**path;
	char	*realpath;
	int		i;

	path = dir_path(shell);
	if (path != NULL)
	{
		i = 0;
		while (path[i] != NULL)
		{
			realpath = ft_strjoin(path[i], cmd);
			if (access(realpath, F_OK) == 0)
			{
				if (access(realpath, X_OK) != 0)
				{
					shell->check = 2;
					break ;
				}
				sh_ex_free_arr(path);
				shell->check = 1;
				return (realpath);
			}
			free(realpath);
			i++;
		}
		sh_ex_free_arr(path);
	}
	return (NULL);
} */

int	file_stat_checks(char *path)
{
	struct stat	file_info;

	if (stat(path, &file_info) == -1 || access(path, X_OK) != 0)
	{
		if (errno == ENOTDIR)
			ft_putstr_fd(" is not a directory\n", STDERR_FILENO);
		else if (errno == EACCES)
		{
			g_shell.exit_info.exit_code = 126;
			ft_putstr_fd(" Permission denied\n", STDERR_FILENO);
		}
		else if (errno == ENOENT)
		{
			g_shell.exit_info.exit_code = 127;
			ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
		}
		return (0);
	}
	if (S_ISDIR(file_info.st_mode))
	{
		g_shell.exit_info.exit_code = 126;
		ft_putstr_fd(" is a directory\n", 2);
		return (0);
	}
	return (1);
}
