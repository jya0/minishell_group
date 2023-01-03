/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_bindir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 04:53:55 by yoyohann          #+#    #+#             */
/*   Updated: 2022/12/27 04:47:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *sh_ex_bindir(t_shell_s *shell, char *cmd)
{
	int i;
	char *realpath;

	i = 0;
	while (shell->path[i])
	{
		realpath = malloc(sizeof(char) *
						  (ft_strlen(shell->path[i] + ft_strlen(cmd) + 1)));
		if (!realpath)
			return (NULL);
		realpath = ft_strjoin(shell->path[i], cmd);
		if (access(realpath, F_OK) == 0)
			return (realpath);
		i++;
	}
	return (NULL);
}
