/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeatilga <zeatilga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:46:58 by zeatilga          #+#    #+#             */
/*   Updated: 2024/03/17 12:42:01 by zeatilga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	manage_pipe_dups(t_sdata *sdata, int *fd)
{
	signal(CTRL_SLASH, handler);
	if (sdata->cmds->next)
	{
		dup2(fd[1], 1);
	}
	if (dispatch_redir_types(sdata))
		return (1);
	return (0);
}

void	next(t_sdata *sdata)
{
	sdata->cmds = sdata->cmds->next;
	exit(1);
}

int	execute_builtins(t_sdata *sdata, int *fd, int save_stdout)
{
	void	(*builtins_array[7])(t_sdata *);

	(builtins_array[0]) = display_env;
	(builtins_array[1]) = shell_export;
	(builtins_array[2]) = shell_unset;
	(builtins_array[3]) = pwd;
	(builtins_array[4]) = echo;
	(builtins_array[5]) = shell_cd;
	(builtins_array[6]) = shell_exit;
	if (sdata->cmds->next)
		dup2(fd[1], 1);
	if (dispatch_redir_types(sdata))
	{
		sdata->lrval = 1;
		if (!(sdata->cmds->builtin_idx >= 0 && sdata->cmds->builtin_idx < 7
				&& sdata->nb_of_cmds == 1))
			next(sdata);
		return (1);
	}
	(builtins_array)[sdata->cmds->builtin_idx](sdata);
	if (sdata->cmds->next)
		close(fd[1]);
	dup2(save_stdout, 1);
	return (clear_fd_stack(sdata->cmds), 0);
}

void	get_child_return_value(t_sdata *sdata, int status)
{
	if (WIFEXITED(status))
		sdata->lrval = (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			sdata->lrval = 130;
		else if (WTERMSIG(status) == SIGQUIT)
		{
			sdata->lrval = 131;
			printf("Quit: 3\n");
		}
	}
}

int	execute_binary(t_sdata *sdata, int *fd)
{
	if (manage_pipe_dups(sdata, fd))
	{
		sdata->lrval = 1;
		sdata->cmds = sdata->cmds->next;
		exit(1);
		putstr_err(" Permission denied");
		return (1);
	}
	if (sdata->cmds->next)
		close(fd[0]);
	if (execve(sdata->cmds->cmd_path, sdata->cmds->argv, sdata->env))
		invalid_cmd(sdata, sdata->cmds);
	return (0);
}
