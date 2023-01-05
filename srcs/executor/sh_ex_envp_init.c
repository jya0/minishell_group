/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_env_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 06:33:52 by yoyohann          #+#    #+#             */
/*   Updated: 2022/12/23 06:51:31 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	vars_count(char **vars)
{
	size_t	i;

	if (vars == NULL || (*vars) == NULL)
		return (0);
	i = 0;
	while (vars[i] != NULL)
		i++;
	return (i);
}

static int	init_malloc_key_val(t_shell_s *shell, size_t vars_count)
{
	shell->envp.env_size = vars_count;
	shell->envp.vars = (t_var_s *)ft_calloc(vars_count + 1, sizeof(t_var_s));
	if (shell->envp.vars == NULL)
		return (-1);
	return (0);
}

char	**sh_ex_get_envp_chain(t_shell_s *shell)
{
	char	**envp_chain;
	char	*tmp_str;
	size_t	index;

	envp_chain = (char **)ft_calloc(shell->envp.env_size + 1, sizeof(char *));
	if (envp_chain == NULL)
		return (NULL);
	index = 0;
	while (index < shell->envp.env_size)
	{
		tmp_str = ft_strjoin(shell->envp.vars[index].key, "=");
		envp_chain[index] = ft_strjoin(tmp_str, shell->envp.vars[index].val);
		free(tmp_str);
		index++;
	}
	return (envp_chain);
}

/*
** function called outside of the loop, right after initshell
*/
void	sh_ex_envp_init(t_shell_s *shell, char **envp)
{
	int		i;
	char	**key_val;
	size_t	c_envp_vars;

	c_envp_vars = vars_count(envp);
	if (c_envp_vars <= 0)
		exit(-1);
	if (init_malloc_key_val(shell, c_envp_vars) != 0)
		exit(-1);
	i = 0;
	while (envp[i])
	{
		key_val = ft_split(envp[i], '=');
		shell->envp.vars[i].key = ft_strdup(key_val[0]);
		if (key_val[1] != NULL)
			shell->envp.vars[i].val = ft_strdup(key_val[1]);
		else
			shell->envp.vars[i].val = ft_calloc(1, sizeof(char));
		sh_ex_free_arr(key_val);
		i++;
	}
	shell->envp.envp_chain = sh_ex_get_envp_chain(shell);
}
