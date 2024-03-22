/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_dispatcher.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeatilga <zeatilga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:47:14 by zeatilga          #+#    #+#             */
/*   Updated: 2024/03/17 11:56:42 by zeatilga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	call_outfile(t_sdata *sdata, char **paths, int out, int i)
{
	int	fd;

	fd = open_outfile(paths[i], out);
	if (fd == -1)
		return (1);
	add_fd_to_stack(sdata, fd);
	if (!sdata->cmds->fd_stack)
		return (1);
	dup2(fd, 1);
	return (0);
}

int	call_infile(t_sdata *sdata, char **paths, int in, int i)
{
	int	fd;

	fd = open_infile(sdata, paths[i], in);
	if (fd == -1)
		return (1);
	add_fd_to_stack(sdata, fd);
	if (!sdata->cmds->fd_stack)
		return (1);
	if (!(sdata->cmds->builtin_idx >= 0 && sdata->cmds->builtin_idx < 7))
		dup2(fd, 0);
	return (0);
}

int	manage_redir_fd(t_sdata *sdata, char **paths, int in, int out)
{
	int		i;

	i = 0;
	while (paths[i])
	{
		if (out)
			if (call_outfile(sdata, paths, out, i))
				return (1);
		if (in)
			if (call_infile(sdata, paths, in, i))
				return (1);
		++i;
	}
	return (0);
}

int	priority_redir_in(t_sdata *sdata)
{
	if (sdata->cmds->type_last_rdr_in == 2)
	{
		if (sdata->cmds->redir_ins)
			if (manage_redir_fd(sdata, sdata->cmds->redir_outs, 1, 0))
				return (1);
		if (sdata->cmds->reddir_heredoc)
			if (manage_redir_fd(sdata, sdata->cmds->reddir_heredoc, 2, 0))
				return (4);
	}
	else
	{
		if (sdata->cmds->reddir_heredoc)
			if (manage_redir_fd(sdata, sdata->cmds->reddir_heredoc, 2, 0))
				return (4);
		if (sdata->cmds->redir_ins)
			if (manage_redir_fd(sdata, sdata->cmds->redir_outs, 1, 0))
				return (1);
	}
	return (0);
}

int	priority_redir_out(t_sdata *sdata)
{
	if (sdata->cmds->type_last_rdr_out == 2)
	{
		if (sdata->cmds->redir_outs)
			if (manage_redir_fd(sdata, sdata->cmds->redir_ins, 0, 1))
				return (2);
		if (sdata->cmds->reddir_append)
			if (manage_redir_fd(sdata, sdata->cmds->reddir_append, 0, 2))
				return (3);
	}
	else
	{
		if (sdata->cmds->reddir_append)
			if (manage_redir_fd(sdata, sdata->cmds->reddir_append, 0, 2))
				return (3);
		if (sdata->cmds->redir_outs)
			if (manage_redir_fd(sdata, sdata->cmds->redir_ins, 0, 1))
				return (2);
	}
	return (0);
}
