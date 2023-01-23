/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 03:14:14 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/20 02:18:47 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_var_s	*copy_vars_except_index(t_shell_s *shell, int index_ignore)
{
	t_var_s	*new_vars;
	int		i;
	int		j;

	new_vars = \
	(t_var_s *)ft_calloc(shell->envp.env_size + 1, sizeof(t_var_s));
	if (new_vars == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (shell->envp.vars[i].key != NULL)
	{
		if (i == index_ignore)
		{
			free(shell->envp.vars[i].key);
			free(shell->envp.vars[i].val);
			i++;
			continue ;
		}
		else
			new_vars[j++] = shell->envp.vars[i++];
	}
	free(shell->envp.vars);
	return (new_vars);
}

static void	sh_ex_del_one_var(t_shell_s *shell, char *key)
{
	int		index;

	if (sh_ex_is_valid_key(key) != 0)
	{
		shell->exit_info.exit_code = EXT_INVALID_KEY_ERR;
		return (ft_putstr_fd(" not a valid identifier\n", STDERR_FILENO));
	}
	index = sh_ex_find_key_index(shell->envp.vars, key);
	if (index >= 0)
	{
		shell->envp.env_size--;
		shell->envp.vars = copy_vars_except_index(shell, index);
		sh_ex_free_arr(shell->envp.envp_chain);
		shell->envp.envp_chain = sh_ex_get_envp_chain(shell);
	}
}

int	sh_ex_unset(t_shell_s *shell, char **var_names)
{
	int	i;

	if (var_names == NULL || *(var_names) == NULL)
		return (0);
	i = 0;
	while (var_names[i] != NULL)
	{
		sh_ex_del_one_var(shell, var_names[i]);
		i++;
	}
	return (shell->exit_info.exit_code);
}
