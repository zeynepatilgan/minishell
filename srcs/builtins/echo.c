/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeatilga <zeatilga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:45:47 by zeatilga          #+#    #+#             */
/*   Updated: 2024/03/01 19:45:50 by zeatilga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_every_arg(char **argv, int start)
{
	int		i;

	i = start;
	while (argv[i])
	{
		write(1, argv[i], len(argv[i]));
		if (argv[i + 1] != NULL)
			write(1, " ", 1);
		++i;
	}
}

int	is_dash_n_option(char *option)
{
	int		i;

	i = 1;
	if (option[0] != '-' && len(option) < 2)
		return (1);
	while (option[i] && option[i] == 'n')
	{
		++i;
	}
	if (option[i])
		return (1);
	return (0);
}

void	echo(t_sdata *sdata)
{
	if (tablen(sdata->cmds->argv) == 1)
	{
		write(1, "\n", 1);
		sdata->lrval = 0;
		return ;
	}
	sdata->lrval = 0;
	if (!is_dash_n_option(sdata->cmds->argv[1]))
	{
		if (tablen(sdata->cmds->argv) == 2)
			return ;
		display_every_arg(sdata->cmds->argv, 2);
		return ;
	}
	else
		display_every_arg(sdata->cmds->argv, 1);
	write(1, "\n", 1);
}
