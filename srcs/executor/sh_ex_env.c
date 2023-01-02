/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:47:27 by yoyohann          #+#    #+#             */
/*   Updated: 2022/12/23 06:55:12 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sh_ex_viewenvp(t_shell_s *shell)
{
	int	i;

	i = 0;
	while (i < shell->envp.env_size)
	{
		printf (WHITE"%s", shell->envp.key[i]);
		printf (WHITE"%c", '=');
		printf (WHITE"%s\n", shell->envp.value[i]);
		i++;
	}
}