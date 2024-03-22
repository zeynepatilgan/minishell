/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeatilga <zeatilga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 19:11:06 by zeatilga          #+#    #+#             */
/*   Updated: 2024/03/17 12:51:17 by zeatilga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	invalid_cmd_path_error(t_sdata *sdata)
{
	if ((sdata->cmds->argv[0][0] == '.' || sdata->cmds->argv[0][0] == '/' )
			&& ft_strchr(sdata->cmds->argv[0] + 2, '/'))
	{
		putstr_err(sdata->cmds->cmd);
		putstr_err(": Permission denied");
		sdata->lrval = 126;
		exit(126);
	}
	else if ((sdata->cmds->argv[0][0] == '.' || sdata->cmds->argv[0][0] == '/' )
			&& sdata->nb_of_cmds > 0)
	{
		putstr_err(sdata->cmds->cmd);
		putstr_err(": No such file or directory\n");
		sdata->lrval = 127;
		exit(127);
	}
	else
	{
		putstr_err(sdata->cmds->cmd);
		putstr_err(": command not found\n");
		sdata->lrval = 127;
		exit(127);
	}
	exit(0);
}

void	valid_cmd_dispatch(t_sdata *sdata, int *fd)
{
	if (sdata->cmds->builtin_idx < 7 && sdata->cmds->builtin_idx != -1)
		execute_builtins(sdata, fd, sdata->save_stdout);
	else if (sdata->cmds->cmd_path)
		execute_binary(sdata, fd);
	else
	{
		invalid_cmd_path_error(sdata);
	}
	exit(0);
}

void	execute_one_cmds(t_sdata *sdata, int *fd)
{
	if (sdata->nb_of_cmds == 1 && sdata->cmds->builtin_idx != -1)
	{
		execute_builtins(sdata, fd, sdata->save_stdout);
	}
	else
		invalid_cmd_path_error(sdata);
}

void	while_for_dispatcher(t_sdata *sdata, int *fd, int last_fdin)
{
	int		pid;

	while (sdata->cmds)
	{
		sdata->cmds->save_stdin = sdata->save_stdin;
		if (sdata->cmds->next)
			pipe (fd);
		pid = fork();
		if (pid == 0)
			valid_cmd_dispatch(sdata, fd);
		if (last_fdin)
			close(last_fdin);
		if (sdata->cmds->next)
		{
			close(fd[1]);
			last_fdin = fd[0];
			dup2(fd[0], 0);
		}
		sdata->cmds = sdata->cmds->next;
	}
}

void	execution_dispatcher(t_sdata *sdata)
{
	int		fd[2];
	int		last_fdin;
	int		status;
	int		i;

	status = 0;
	last_fdin = 0;
	if ((sdata->cmds->builtin_idx >= 0 && sdata->cmds->builtin_idx < 7)
		&& sdata->nb_of_cmds == 1)
		execute_one_cmds(sdata, fd);
	if (!(sdata->cmds->builtin_idx >= 0 && sdata->cmds->builtin_idx < 7
			&& sdata->nb_of_cmds == 1))
	{
		while_for_dispatcher(sdata, fd, last_fdin);
		dup2 (sdata->save_stdin, 0);
		i = -1;
		while (++i < sdata->nb_of_cmds)
			waitpid(-1, &status, 0);
		get_child_return_value(sdata, status);
	}
}
