/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_export_add.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 18:13:43 by jyao              #+#    #+#             */
/*   Updated: 2023/01/06 00:09:54 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	does_key_already_exist(t_var_s *vars, char *new_key)
{
	int	i;

	if (new_key == NULL)
		return (-1);
	i = 0;
	while (vars[i].key != NULL)
	{
		if (ft_strcmp(vars[i].key, new_key) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static void	add_one_var(t_shell_s *shell, char *var, char **key_val)
{
	sh_ex_free_arr(shell->envp.envp_chain);
	shell->envp.env_size++;
	shell->envp.vars = \
	sh_ex_realloc_vars(shell->envp.vars, shell->envp.env_size);
	shell->envp.vars[shell->envp.env_size - 1].key = ft_strdup(key_val[0]);
	shell->envp.vars[shell->envp.env_size - 1].val = ft_strdup(key_val[1]);
	if (ft_strchr(var, '=') != NULL && key_val[1] == NULL)
		shell->envp.vars[shell->envp.env_size - 1].val = ft_strdup("");
	shell->envp.envp_chain = sh_ex_get_envp_chain(shell);
}

static void	replace_one_var(\
t_shell_s *shell, char *var, char **key_val, int i)
{
	if (ft_strchr(var, '=') == NULL)
		return ;
	if (shell->envp.vars[i].val != NULL)
		free(shell->envp.vars[i].val);
	shell->envp.vars[i].val = ft_strdup(key_val[1]);
	if (ft_strchr(var, '=') != NULL && key_val[1] == NULL)
		shell->envp.vars[i].val = ft_strdup("");
}

static int	envp_edit_one_var(t_shell_s *shell, char *var)
{
	char	**key_val;
	int		i;

	if (var == NULL)
		return (-1);
	key_val = ft_split(var, '=');
	i = does_key_already_exist(shell->envp.vars, key_val[0]);
	if (i < 0)
		add_one_var(shell, var, key_val);
	else
		replace_one_var(shell, var, key_val, i);
	sh_ex_free_arr(key_val);
	return (0);
}

int	sh_ex_export_add_vars(t_shell_s *shell, char **vars)
{
	size_t	i;

	if (vars == NULL || (*vars) == NULL)
		return (-1);
	i = 0;
	while (vars[i] != NULL)
	{
		envp_edit_one_var(shell, vars[i]);
		i++;
	}
	return (0);
}
