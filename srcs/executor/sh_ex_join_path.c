/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_join_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 01:06:45 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/24 00:59:23 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

	if (*cmd == '/')
	{
		realpath = absolute_path(cmd);
		if (realpath != NULL)
			return (realpath);
	}
	else if (ft_strchr(cmd, '/') != NULL)
	{
		realpath = relative_path(sh_ex_cwd(), cmd);
		if (realpath != NULL)
			return (realpath);
	}
	else
	{
		realpath = path_var_path(shell, cmd);
		if (realpath != NULL)
			return (realpath);
	}
	return (NULL);
}
