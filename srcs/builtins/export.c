/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeatilga <zeatilga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:46:11 by zeatilga          #+#    #+#             */
/*   Updated: 2024/03/16 16:56:55 by zeatilga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export_display(t_sdata *sdata)
{
	t_env_lst	*list;

	if (!sdata->env_lst)
		return ;
	list = sdata->env_lst;
	while (list)
	{
		printf("declare -x %s", list->name);
		if (list->var)
		{
			printf("=\"%s\"\n", list->var);
		}
		else
			printf("\n");
		list = list->next;
	}
}

void	usage_export_replace_var(t_sdata *sdata, char *arg)
{
	sdata->env_lst = remove_elem(sdata->env_lst, arg);
	sdata->env_lst = add_elem(sdata->env_lst, arg);
	sdata->env = remove_str_from_arr(sdata->env, arg);
	sdata->env = cncat_arr(sdata->env, arg);
	if (arg)
		free(arg);
}

void	export_replace_var(t_sdata *sdata)
{
	sdata->env_lst = remove_elem(sdata->env_lst, sdata->cmds->argv[1]);
	sdata->env_lst = add_elem(sdata->env_lst, sdata->cmds->argv[1]);
	sdata->env = remove_str_from_arr(sdata->env, sdata->cmds->argv[1]);
	sdata->env = cncat_arr(sdata->env, sdata->cmds->argv[1]);
}

void	shell_export(t_sdata *sdata)
{
	if (tablen(sdata->cmds->argv) == 1)
	{
		export_display(sdata);
		sdata->lrval = 0;
		return ;
	}
	if (is_env_var_valid(sdata->cmds->argv[1], 0))
	{
		sdata->lrval = 1;
		return ;
	}
	if (does_env_var_exist(sdata->env_lst, sdata->cmds->argv[1]))
	{
		export_replace_var(sdata);
		sdata->lrval = 0;
		return ;
	}
	sdata->env = cncat_arr(sdata->env, sdata->cmds->argv[1]);
	sdata->env_lst = add_elem(sdata->env_lst, sdata->cmds->argv[1]);
	sdata->lrval = 0;
}
