/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:18:27 by jyao              #+#    #+#             */
/*   Updated: 2022/12/12 15:27:03 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// check where the executable file is in the bin path
// and return it if found 
char *sh_ex_bindir(t_shell_s *shell, char *cmd)
{
    int i;
    char *realpath;

    i = 0;
    while (shell->path[i])
    {
        realpath = malloc(sizeof(char) * (ft_strlen(shell->path[i] + ft_strlen(cmd) + 1)));
        if (!realpath)
            return (NULL);
        realpath = ft_strjoin(shell->path[i], cmd);
        // check if the file is found in the directory if found 
        // return it
        if (access(realpath, F_OK) == 0)
            return (realpath);
        i++;
    }
    free(realpath);
    return (NULL);
}

sh_ps_