/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_bindir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 04:53:55 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/09 22:42:01 by jyao             ###   ########.fr       */
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

static char	*absolute_path(char *cwd, char *path)
{
	char	*cwd_w_slash;
	char	*absolute_path;

	cwd_w_slash = ft_strjoin(cwd, "/");
	free(cwd);
	absolute_path = ft_strjoin(cwd_w_slash, path);
	free(cwd_w_slash);
	return (absolute_path);
}

char	*sh_ex_bindir(t_shell_s *shell, char *cmd)
{
	int		i;
	char	*realpath;
	char	**path;

	path = dir_path(shell);
	if (path != NULL)
	{
		i = 0;
		while (path[i] != NULL)
		{
			realpath = ft_strjoin(path[i], cmd);
			if (realpath == NULL)
				break ;
			if (access(realpath, F_OK) == 0)
			{
				sh_ex_free_arr(path);
				return (realpath);
			}
			free(realpath);
			i++;
		}
		sh_ex_free_arr(path);
	}
	else
	{
		realpath = absolute_path(sh_ex_cwd(), cmd);
		printf("%s\n", realpath);
		if (access(realpath, F_OK) != 0)
		{
			free(realpath);
			printf("FILE EXECUTION error\n");
			return (NULL);
		}
		return (realpath);
	}
	return (NULL);
}
