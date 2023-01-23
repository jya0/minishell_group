/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_join_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 01:06:45 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/23 02:06:32 by yoyohann         ###   ########.fr       */
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

char	**dir_path(t_shell_s *shell)
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

static char	*absolute_path(char *absolute_path)
{
	if (absolute_path == NULL)
		return (NULL);
	if (file_stat_checks(absolute_path) == 0)
		return (NULL);
	else
		return (ft_strdup(absolute_path));
}

static char	*relative_path(char *cwd, char *path)
{
	char			*cwd_w_slash;
	char			*relative_path;

	cwd_w_slash = ft_strjoin(cwd, "/");
	free(cwd);
	relative_path = ft_strjoin(cwd_w_slash, path);
	free(cwd_w_slash);
	if (cwd_w_slash == NULL || relative_path == NULL)
		return (free(cwd_w_slash), free(relative_path), NULL);
	if (file_stat_checks(relative_path) == 1)
		return (relative_path);
	else
	{
		free(relative_path);
		relative_path = NULL;
		return (NULL);
	}
}

char	*sh_ex_bindir(t_shell_s *shell, char *cmd)
{
	char	*realpath;

	if (*cmd == '.')
	{
		realpath = relative_path(sh_ex_cwd(), cmd);
		if (realpath != NULL)
			return (realpath);
	}
	else if (*cmd == '/')
	{
		realpath = absolute_path(cmd);
		if (realpath != NULL)
			return (realpath);
	}
	else if (*cmd != '\0')
	{
		realpath = path_var_path(shell, cmd);
		if (realpath != NULL)
			return (realpath);
		else if (shell->check == 0)
			ft_putstr_fd(" command not found\n", STDERR_FILENO);
		else if (shell->check == 2)
			ft_putstr_fd(" Permission denied\n", STDERR_FILENO);
	}
	return (NULL);
}
