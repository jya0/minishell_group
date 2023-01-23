/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_check_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 00:09:29 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/24 01:02:23 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** we use ft_strdup here for it because, absolute_path is
** entered in the command line and will be freed later using
** sh_ps_free_command_list
** for consistency with the previous realpath
 if conditions
** it's necessary to malloc here.
*/

static char	**dir_path(t_shell_s *shell)
{
	int		i;
	char	*all_path;
	char	**path;
	char	**dir_path;	

	all_path = sh_ex_searchenvvar(shell, "PATH");
	if (all_path != NULL)
	{
		path = ft_split(all_path, ':');
		dir_path = malloc(sizeof(char *) * (sh_ex_doublelen(path) + 1));
		if (dir_path == NULL)
			return (NULL);
		i = 0;
		while (path[i])
		{
			dir_path[i] = ft_strjoin(path[i], "/");
			i++;
		}
		dir_path[i] = NULL;
		sh_ex_free_arr(path);
		return (dir_path);
	}
	shell->exit_info.exit_code = 127;
	return (NULL);
}

static char	*exec_path(t_shell_s *shell, char **path, char *cmd)
{
	int		i;
	char	*realpath;

	i = 0;
	if (*cmd != '\0')
	{
		while (path[i] != NULL)
		{
			realpath = ft_strjoin(path[i], cmd);
			if (access(realpath, F_OK) == 0)
			{
				if (access(realpath, X_OK) != 0)
				{
					ft_putstr_fd(" Permission denied\n", STDERR_FILENO);
					free(realpath);
					return (NULL);
				}
				return (realpath);
			}
			free(realpath);
			i++;
		}
	}
	shell->exit_info.exit_code = 127;
	return (NULL);
}

char	*path_var_path(t_shell_s *shell, char *cmd)
{
	char	**path;
	char	*realpath;

	path = NULL;
	realpath = NULL;
	if (*cmd != '.')
	{
		path = dir_path(shell);
		if (path != NULL)
		{
			realpath = exec_path(shell, path, cmd);
			sh_ex_free_arr(path);
			if (realpath != NULL)
				return (realpath);
		}
	}
	else
		shell->exit_info.exit_code = 127;
	if (shell->exit_info.exit_code == 127)
		ft_putstr_fd(" command not found\n", STDERR_FILENO);
	return (NULL);
}

static void	stat_error_messages(int err)
{
	if (err == ENOTDIR)
	{
		g_shell.exit_info.exit_code = 126;
		ft_putstr_fd(" is not a directory\n", STDERR_FILENO);
	}
	else if (err == EACCES)
	{
		g_shell.exit_info.exit_code = 126;
		ft_putstr_fd(" Permission denied\n", STDERR_FILENO);
	}
	else if (err == ENOENT)
	{
		g_shell.exit_info.exit_code = 127;
		ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
	}
}

int	file_stat_checks(char *path)
{
	struct stat	file_info;

	if (stat(path, &file_info) == -1 || access(path, X_OK) != 0)
	{
		stat_error_messages(errno);
		return (0);
	}
	if (S_ISDIR(file_info.st_mode))
	{
		g_shell.exit_info.exit_code = 126;
		ft_putstr_fd(" is a directory\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}
