/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:20:24 by yoyohann          #+#    #+#             */
/*   Updated: 2022/12/23 08:41:49 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*sh_ex_cwd(void)
{
	char	*cwd;
	char	cwd_str[1024];

	getcwd (cwd_str, sizeof (cwd_str));
	cwd = ft_strdup (cwd_str);
	return (cwd);
}

void	sh_ex_showpwd(t_shell_s *shell)
{
	char	*dir;

	dir = sh_ex_cwd ();
	if (dir == NULL)
		sh_ex_exitstatus = 1;
	else
	{
		sh_ex_exitstatus = 0;
		dir = ft_strjoin (WHITE, dir);
		ft_putstr_fd (dir, shell->fdout);
		ft_putchar_fd ('\n', shell->fdout);
	}
	free (dir);
}
