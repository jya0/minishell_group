/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:20:24 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/07 22:46:10 by yoyohann         ###   ########.fr       */
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

int	sh_ex_showpwd(void)
{
	char	*dir;
	char	*tmp;

	dir = sh_ex_cwd ();
	if (dir == NULL)
		g_shell.exit_info.exit_code = 1;
	else
	{
		g_shell.exit_info.exit_code = 0;
		tmp = ft_strjoin (WHITE, dir);
		free(dir);
		ft_putstr_fd (tmp, STDOUT_FILENO);
		ft_putchar_fd ('\n', STDOUT_FILENO);
		free (tmp);
	}
	return (0);
}
