/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_bindir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 04:53:55 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/06 01:50:59 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*sh_ex_bindir(t_shell_s *shell, char *cmd)
{
	int		i;
	char	*realpath;

	i = 0;
	while (shell->path[i])
	{
		realpath = ft_strjoin(shell->path[i], cmd);
		if (realpath == NULL)
			break ;
		if (access(realpath, F_OK) == 0)
			return (realpath);
		free(realpath);
		i++;
	}
	return (NULL);
}
