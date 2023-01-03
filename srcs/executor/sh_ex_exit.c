/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 02:51:59 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/01 20:06:55 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_ex_exit(t_shell_s *shell)
{
	sh_ex_freeall (shell->path);
	free (shell->home);
	free (shell->cwd);
	write (1, "exit\n", 5);
	exit (0);
}
