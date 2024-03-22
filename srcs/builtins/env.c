/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeatilga <zeatilga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:45:56 by zeatilga          #+#    #+#             */
/*   Updated: 2024/03/01 19:45:59 by zeatilga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_env(t_sdata *sdata)
{
	t_env_lst		*list;

	list = sdata->env_lst;
	while (list)
	{
		if (!list->var)
		{
			list = list->next;
			continue ;
		}
		write(1, list->name, len(list->name));
		write(1, "=", 1);
		write(1, list->var, len(list->var));
		write(1, "\n", 1);
		list = list->next;
	}
	sdata->lrval = 0;
}
