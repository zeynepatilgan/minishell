/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_stack_manage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksin <taksin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:47:05 by zeatilga          #+#    #+#             */
/*   Updated: 2024/03/10 12:42:49 by taksin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	*extend_fd_stack(int *fd_stack, int fd_len, int fd)
{
	int		i;
	int		*nfd_stack;

	i = 0;
	nfd_stack = malloc(sizeof(int) * (fd_len + 1));
	if (!nfd_stack)
		return (NULL);
	while (i < fd_len)
	{
		nfd_stack[i] = fd_stack[i];
		++i;
	}
	nfd_stack[i] = fd;
	return (nfd_stack);
}

void	add_fd_to_stack(t_sdata *sdata, int fd)
{
	if (!sdata->cmds->fd_stack)
	{
		sdata->cmds->fd_stack = malloc(sizeof(int));
		if (!sdata->cmds->fd_stack)
		{
			sdata->cmds->fd_nbr = 0;
			return ;
		}
		sdata->cmds->fd_stack[0] = fd;
		sdata->cmds->fd_nbr = 1;
	}
	else
	{
		sdata->cmds->fd_stack = extend_fd_stack(sdata->cmds->fd_stack,
				sdata->cmds->fd_nbr, fd);
		if (!sdata->cmds->fd_stack)
		{
			sdata->cmds->fd_nbr = 0;
			return ;
		}
		(sdata->cmds->fd_nbr)++;
	}
}

void	clear_fd_stack(t_cmd_lst *cmds)
{
	int		i;

	i = 0;
	while (i < cmds->fd_nbr)
	{
		close(cmds->fd_stack[i]);
		++i;
	}
	free(cmds->fd_stack);
	cmds->fd_stack = NULL;
	cmds->fd_nbr = 0;
}
