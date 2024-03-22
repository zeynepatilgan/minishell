/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksin <taksin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:46:04 by zeatilga          #+#    #+#             */
/*   Updated: 2024/03/10 13:44:19 by taksin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	shell_exit(t_sdata *sdata)
{
	if (sdata->cmds->argv == NULL || tablen(sdata->cmds->argv) == 1)
	{
		printf("exit\n");
		exit(sdata->lrval);
	}
	if (is_number(sdata->cmds->argv[1], 0) != len(sdata->cmds->argv[1]))
	{
		if (ft_atoi(sdata->cmds->argv[1]))
			exit(ft_atoi(sdata->cmds->argv[1]));
		else
		{
			putstr_err(" numeric argument required\n");
			exit (255);
		}
	}
	if (is_number(sdata->cmds->argv[1], 0) == len(sdata->cmds->argv[1]))
	{
		if (tablen(sdata->cmds->argv) == 2)
			exit(ft_atoi(sdata->cmds->argv[1]));
		else
		{
			putstr_err(" too many arguments\n");
			sdata->lrval = 1;
		}
	}
}

int	usage_exit(char **argv)
{
	if (!argv)
	{
		printf("exit\n");
		exit(0);
	}
	if (!is_number(argv[1], 0))
	{
		putstr_err(" numeric argument required\n");
		exit(ft_atoi(argv[1]));
	}
	if (is_number(argv[1], 0))
	{
		if (tablen(argv) == 1)
			exit(ft_atoi(argv[1]));
		else
		{
			putstr_err(" too many arguments\n");
			return (1);
		}
	}
	return (1);
}
