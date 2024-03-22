/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeatilga <zeatilga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:58:32 by zeatilga          #+#    #+#             */
/*   Updated: 2024/03/10 17:18:56 by zeatilga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	manage_for_common_heredoc(char *line, int fd, char *limit)
{
	get_next_line(0, &line);
	while (ft_strncmp(limit, line, len(limit)))
	{
		write(fd, line, len(line));
		free(line);
		line = NULL;
		write(fd, "\n", 1);
		write(1, ">", 1);
		get_next_line(0, &line);
	}
}

int	manage_heredoc(t_sdata *sdata, char *limit, int l_fd_in, int save_stdin)
{
	char	*line;
	int		fd;

	if ((sdata->cmds->builtin_idx >= 0 && sdata->cmds->builtin_idx < 7)
		&& sdata->nb_of_cmds == 1)
	{
		fd = manage_heredoc_fork(limit, l_fd_in, save_stdin);
		return (fd);
	}
	else
	{
		dup2(save_stdin, 0);
		fd = open("/tmp/.tmp_heredoc", O_RDWR | O_TRUNC);
		if (fd == -1)
			fd = open("/tmp/.tmp_heredoc", O_RDWR | O_CREAT, 0666);
		g_signal = 10;
		line = NULL;
		write(1, ">", 1);
		manage_for_common_heredoc(line, fd, limit);
		close(fd);
		fd = open("/tmp/.tmp_heredoc", O_RDONLY);
		dup2(l_fd_in, 0);
		return (fd);
	}
	return (0);
}

int	manage_heredoc_fork(char *limit, int l_fd_in, int save_stdin)
{
	char	*line;
	int		fd;
	int		pid;
	int		status;

	pid = 0;
	status = 0;
	dup2(save_stdin, 0);
	pid = fork();
	fd = open("/tmp/.tmp_heredoc", O_RDWR | O_TRUNC);
	if (pid == 0)
	{
		fd = open("/tmp/.tmp_heredoc", O_RDWR | O_TRUNC);
		if (fd == -1)
			fd = open("/tmp/.tmp_heredoc", O_RDWR | O_CREAT, 0666);
		g_signal = 10;
		line = NULL;
		write(1, ">", 1);
		manage_for_common_heredoc(line, fd, limit);
		close(fd);
		exit(0);
	}
	waitpid(pid, &status, 0);
	fd = open("/tmp/.tmp_heredoc", O_RDONLY);
	return (dup2(l_fd_in, 0), fd);
}
