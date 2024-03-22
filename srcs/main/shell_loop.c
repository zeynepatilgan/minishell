/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksin <taksin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:45:23 by zeatilga          #+#    #+#             */
/*   Updated: 2024/03/10 14:31:55 by taksin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	send_to_exec(t_sdata *sdata)
{
	execution_dispatcher(sdata);
	deallocate_cmd_list(sdata->f_cmds);
	sdata->cmds = NULL;
	sdata->f_cmds = NULL;
}

int	shell_loop(t_sdata *sdata)
{
	char	*line;

	line = NULL;
	while_for_shell_loop(sdata, line);
	return (sdata->lrval);
}

int	check_line(char *line)
{
	if (quotes_check(line) == -1 || !line
		|| redir_check(line) == -1)
		return (-1);
	if (pipe_check(line) == -1)
	{
		printf("minishell: parse error near '|'\n");
		return (-1);
	}
	return (pipe_check(line));
}

char	rdr_check(char *cmd, int i)
{
	if ((cmd[i] == '>' && cmd[i + 1] == '>')
		|| (cmd[i] == '<' && cmd[i + 1] == '<'))
	{
		if (!cmd[skip_blank(cmd + i + 2) + i + 2]
			|| cmd[skip_blank(cmd + i + 2) + i + 2] == '>'
			|| cmd[skip_blank(cmd + i + 2) + i + 2] == '<' )
			return (cmd[i]);
	}
	else if ((cmd[i] == '>' || cmd[i] == '<')
		&& (cmd[skip_blank(cmd + i + 1) + i + 1] == '|'
			|| cmd[skip_blank(cmd + i + 1) + i + 1] == '<'
			|| cmd[i + 1] == '<' || cmd[i + 1] == '>'
			|| cmd[skip_blank(cmd + i + 1) + i + 1] == '>'
			|| !cmd[skip_blank(cmd + i + 1) + i + 1]))
		return (cmd[i]);
	return (0);
}

int	redir_check(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		i = find_quotes(cmd, i, cmd[i]);
		if (rdr_check(cmd, i) != 0)
		{
			printf("minishell: parse error near '%c'\n", cmd[i]);
			return (-1);
		}
		i++;
	}
	return (0);
}
