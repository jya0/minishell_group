/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_bindir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 04:53:55 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/11 15:50:20 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	return (NULL);
}

static char	*path_var_path(t_shell_s *shell, char *cmd)
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
			if (realpath == NULL || access(realpath, F_OK) == 0)
			{
				sh_ex_free_arr(path);
				return (realpath);
			}
			free(realpath);
			i++;
		}
		sh_ex_free_arr(path);
	}
	return (NULL);
}

static char	*relative_path(char *cwd, char *path)
{
	char	*cwd_w_slash;
	char	*relative_path;

	cwd_w_slash = ft_strjoin(cwd, "/");
	free(cwd);
	relative_path = ft_strjoin(cwd_w_slash, path);
	free(cwd_w_slash);
	if (cwd_w_slash == NULL || relative_path == NULL)
		return (free(cwd_w_slash), free(relative_path), NULL);
	if (access(relative_path, F_OK) != 0)
	{
		free(relative_path);
		relative_path = NULL;
		return (NULL);
	}
	return (relative_path);
}

/*
** we use ft_strdup here for it because, absolute_path is
** entered in the command line and will be freed later using
** sh_ps_free_command_list
** for consistency with the previous realpath if conditions
** it's necessary to malloc here.
*/
static char	*absolute_path(char *absolute_path)
{
	if (absolute_path == NULL)
		return (NULL);
	if (access(absolute_path, F_OK) == 0)
		return (ft_strdup(absolute_path));
	return (NULL);
}

char	*sh_ex_bindir(t_shell_s *shell, char *cmd)
{
	char	*realpath;

	realpath = path_var_path(shell, cmd);
	if (realpath != NULL)
		return (realpath);
	realpath = relative_path(sh_ex_cwd(), cmd);
	if (realpath != NULL)
		return (realpath);
	realpath = absolute_path(cmd);
	if (realpath != NULL)
		return (realpath);
	return (NULL);
}
