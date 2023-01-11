/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 08:23:28 by yoyohann          #+#    #+#             */
/*   Updated: 2022/12/23 08:33:46 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_ex_doublelen(char **str)
{
	int	i;

	i = 0;
	if (str == NULL || *str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	sh_ex_free_arr(char **str)
{
	int	i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str[i]);
	free(str);
	str = NULL;
}

void	sh_ex_free_loop(t_shell_s *shell)
{
	free(shell->cmd_line);
	sh_ps_parser_commands_free_list(shell->head_command);
}

void	sh_ex_free_vars(t_var_s *vars)
{
	size_t	i;

	i = 0;
	while (vars[i].key != NULL)
	{
		if (vars[i].key != NULL)
			free(vars[i].key);
		if (vars[i].val != NULL)
			free(vars[i].val);
		i++;
	}
	free(vars);
}

void	sh_ex_free_all(t_shell_s *shell)
{
	rl_clear_history();
	sh_ex_free_vars(shell->envp.vars);
	sh_ex_free_arr(shell->envp.envp_chain);
	sh_ex_free_loop(shell);
}
