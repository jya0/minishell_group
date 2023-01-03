/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:20:24 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/03 19:26:35 by yoyohann         ###   ########.fr       */
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

	dir = sh_ex_cwd ();
	if (dir == NULL)
		sh_ex_exitstatus = 1;
	else
	{
		sh_ex_exitstatus = 0;
		dir = ft_strjoin (WHITE, dir);
		ft_putstr_fd (dir, STDOUT_FILENO);
		ft_putchar_fd ('\n', STDOUT_FILENO);
	}
	free (dir);
	return (0);
}
