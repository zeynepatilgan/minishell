/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirection_fd_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksin <taksin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:35:43 by taksin            #+#    #+#             */
/*   Updated: 2024/03/10 15:13:41 by taksin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_outfile(char *path, int in)
{
	int		fd;

	if (in == 1)
		fd = open(path, O_RDWR | O_TRUNC);
	else
		fd = open(path, O_RDWR | O_APPEND);
	if (fd == -1)
		fd = open(path, O_RDWR | O_CREAT, 0666);
	return (fd);
}

int	open_infile(t_sdata *sdata, char *path, int out)
{
	int		fd;

	if (out == 2)
		fd = manage_heredoc(sdata, path, sdata->cmds->last_fd_in,
				sdata->cmds->save_stdin);
	else
		fd = open(path, O_RDONLY);
	if (fd == -1)
		putstr_err(" No such file or directory\n");
	sdata->cmds->last_fd_in = fd;
	return (fd);
}

int	dispatch_redir_types(t_sdata *sdata)
{
	if (priority_redir_in(sdata))
		return (1);
	if (priority_redir_out(sdata))
		return (1);
	return (0);
}

void	invalid_cmd(t_sdata *sdata, t_cmd_lst *cmds)
{
	putstr_err(cmds->cmd);
	putstr_err(": is a directory\n");
	deallocate_sdata(sdata);
	exit(126);
}
