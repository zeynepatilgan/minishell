/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeatilga <zeatilga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:46:23 by zeatilga          #+#    #+#             */
/*   Updated: 2024/03/01 19:46:26 by zeatilga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	shell_unset(t_sdata *sdata)
{
	if (sdata->cmds->argv[1] && (is_env_var_valid(sdata->cmds->argv[1], 1)))
	{
		sdata->lrval = 1;
		return ;
	}
	if (!sdata->cmds->argv[1]
		|| !does_env_var_exist(sdata->env_lst, sdata->cmds->argv[1]))
	{
		sdata->lrval = 0;
		return ;
	}
	sdata->env = remove_str_from_arr(sdata->env, sdata->cmds->argv[1]);
	sdata->env_lst = remove_elem(sdata->env_lst, sdata->cmds->argv[1]);
	sdata->lrval = 0;
}

int	usage_unset(char ***env, char *var)
{
	char	**n_env;
	int		i;

	i = 0;
	if (!is_env_var_valid(var, 1))
		return (1);
	if (get_idx_var_in_env(*env, var) == -1)
		return (0);
	n_env = malloc(sizeof(char *) * (tablen(*env) - 1));
	if (!n_env)
		return (1);
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], var, len(var)))
			n_env[i] = (*env)[i];
		++i;
	}
	n_env[i] = NULL;
	free(*env);
	*env = n_env;
	return (0);
}
