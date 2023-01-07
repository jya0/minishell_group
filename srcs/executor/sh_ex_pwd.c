/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:20:24 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/07 21:19:37 by yoyohann         ###   ########.fr       */
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
		sh_ex_exitstatus = 1;
	else
	{
		sh_ex_exitstatus = 0;
		tmp = ft_strjoin (WHITE, dir);
		free(dir);
		ft_putstr_fd (tmp, STDOUT_FILENO);
		ft_putchar_fd ('\n', STDOUT_FILENO);
		free (tmp);
	}
	return (0);
}
