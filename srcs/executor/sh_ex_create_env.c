/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_create_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 04:11:18 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/05 04:19:09 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void sh_ex_init_key_val(t_shell_s *shell)
{
    shell->envp.key = malloc (sizeof(char *) * (shell->envp.env_size + 1));
	if (!shell->envp.key)
		exit(EXIT_FAILURE);
	shell->envp.value = malloc (sizeof(char *) * (shell->envp.env_size + 1));
	if (!shell->envp.value)
		exit(EXIT_FAILURE);
}

void sh_ex_create_key(t_shell_s *shell, char **envp)
{
    int i;
    char **temp_env;
    
    shell->envp.key = malloc (sizeof(char *) * (shell->envp.env_size + 1));
	if (!shell->envp.key)
		exit(EXIT_FAILURE);
}
void sh_ex_create_key_val(t_shell_s *shell)