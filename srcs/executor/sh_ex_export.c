/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 19:30:00 by jyao              #+#    #+#             */
/*   Updated: 2023/01/23 21:45:03 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	var_swap(t_var_s *var1, t_var_s *var2)
{
	t_var_s	tmp_var;

	tmp_var = (t_var_s){0};
	if (ft_strcmp(var1->key, var2->key) > 0)
	{
		tmp_var = *var1;
		*var1 = *var2;
		*var2 = tmp_var;
	}
}

static t_var_s	*sort_vars(t_shell_s *shell, t_var_s *vars)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = shell->envp.env_size;
	while (i < (len - 1))
	{
		j = i + 1;
		while (j < len)
		{
			var_swap(&(vars[i]), &(vars[j]));
			j++;
		}
		i++;
	}
	return (vars);
}

static	void	display_value(char *value)
{
	size_t	i;

	ft_putstr_fd("=", STDOUT_FILENO);
	ft_putchar_fd('"', STDOUT_FILENO);
	i = 0;
	while (value[i] != '\0')
	{
		if (ft_strchr("\"$", value[i]) != NULL)
			ft_putchar_fd('\\', STDOUT_FILENO);
		ft_putchar_fd(value[i++], STDOUT_FILENO);
	}
	ft_putchar_fd('"', STDOUT_FILENO);
}

static int	export_display(t_shell_s *shell)
{
	t_var_s	*tmp_vars;
	char	*val;
	size_t	i;

	tmp_vars = sh_ex_dup_vars(shell->envp.vars);
	if (tmp_vars == NULL)
		return (-1);
	sort_vars(shell, tmp_vars);
	i = 0;
	while (tmp_vars[i].key != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(tmp_vars[i].key, STDOUT_FILENO);
		val = sh_ex_searchenvvar(shell, tmp_vars[i].key);
		if (val != NULL)
			display_value(val);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	free(tmp_vars);
	return (0);
}

int	sh_ex_export(t_shell_s *shell, char **vars)
{
	if (vars == NULL || *(vars) == NULL)
		export_display(shell);
	else
		sh_ex_export_add_vars(shell, vars);
	return (shell->exit_info.exit_code);
}
