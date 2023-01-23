/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_export_add.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 18:13:43 by jyao              #+#    #+#             */
/*   Updated: 2023/01/20 02:18:17 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_ex_find_key_index(t_var_s *vars, char *key)
{
	int	i;

	if (key == NULL)
		return (-1);
	i = 0;
	while (vars[i].key != NULL)
	{
		if (ft_strcmp(vars[i].key, key) == 0)
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
t_shell_s *shell, char *addr_e_sign, char **key_val, int i)
{
	if (addr_e_sign == NULL)
		return ;
	if (shell->envp.vars[i].val != NULL)
		free(shell->envp.vars[i].val);
	shell->envp.vars[i].val = ft_strdup(key_val[1]);
	if (addr_e_sign != NULL && key_val[1] == NULL)
		shell->envp.vars[i].val = ft_strdup("");
}

static int	envp_edit_one_var(t_shell_s *shell, \
char *addr_e_sign, char *vararg, char **key_val)
{
	int		i;

	if (key_val == NULL)
		return (-1);
	if (sh_ex_is_valid_key(key_val[0]) != 0)
	{
		shell->exit_info.exit_code = EXT_INVALID_KEY_ERR;
		return (ft_putstr_fd(" not a valid identifier\n", STDERR_FILENO), -1);
	}
	i = sh_ex_find_key_index(shell->envp.vars, key_val[0]);
	if (i < 0)
		add_one_var(shell, vararg, key_val);
	else
		replace_one_var(shell, addr_e_sign, key_val, i);
	return (0);
}

int	sh_ex_export_add_vars(t_shell_s *shell, char **vars)
{
	size_t	i;
	char	*key_val[2];
	char	*addr_e_sign;

	if (vars == NULL || (*vars) == NULL)
		return (-1);
	i = 0;
	while (vars[i] != NULL)
	{
		ft_bzero(key_val, sizeof(char *) * 2);
		addr_e_sign = ft_strchr(vars[i], '=');
		if (addr_e_sign == NULL)
			key_val[0] = ft_strdup(vars[i]);
		else
		{
			key_val[0] = ft_substr(vars[i], 0, addr_e_sign - vars[i]);
			key_val[1] = ft_substr(vars[i], addr_e_sign - vars[i] + 1, \
			ft_strlen(vars[i]));
		}
		envp_edit_one_var(shell, addr_e_sign, vars[i], key_val);
		free(key_val[0]);
		free(key_val[1]);
		i++;
	}
	return (0);
}
