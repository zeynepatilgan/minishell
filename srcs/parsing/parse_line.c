/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeatilga <zeatilga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:48:30 by zeatilga          #+#    #+#             */
/*   Updated: 2024/03/16 15:15:28 by zeatilga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd_lst	*parse_line(t_sdata *sdata, char *line)
{
	t_cmd_lst	*cmd;
	t_cmd_lst	*firstcmd;
	char		**mul_cmd;
	int			i;

	i = 0;
	cmd = init_linkedlist();
	firstcmd = cmd;
	mul_cmd = split_the_pipe(line);
	while (i < sdata->nb_of_cmds)
	{
		if (i != 0)
			cmd = insertion_linklist(cmd);
		fill_cmds(sdata, cmd, mul_cmd[i]);
		if (cmd->builtin_idx == -1 && cmd->argv[0])
			cmd->cmd_path = is_cmd_executable(cmd->cmd, sdata);
		i++;
	}
	free_arr(mul_cmd);
	return (firstcmd);
}

int	pipe_check(char *str)
{
	int	i;
	int	blank;
	int	cmd;

	cmd = 1;
	blank = -1;
	i = 0;
	while (str[i])
	{
		i = find_quotes(str, i, str[i]);
		if (str[i] == '|')
		{
			cmd++;
			if (i == (int)len(str) - 1 || i == 0 || blank == -1)
				return (-1);
			blank = -1;
		}
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '|')
			blank = 0;
		i++;
	}
	if (blank != -1)
		return (cmd);
	return (blank);
}

int	quotes_check(char *str)
{
	t_quote	qt;
	int		i;

	qt.double_q = 0;
	qt.simple_q = 0;
	i = 0;
	while (str[i])
	{
		checkquotes(str[i], &qt);
		i++;
	}
	if (qt.simple_q % 2 != 0)
	{
		printf("minishell: unexpected EOF while looking for matching '\''\n");
		return (-1);
	}
	if (qt.double_q % 2 != 0)
	{
		printf("minishell: unexpected EOF while looking for matching '\"'\n");
		return (-1);
	}
	return (0);
}

int	checkquotes(char c, t_quote *qt)
{
	if (c == '\"')
	{
		if (qt->simple_q % 2 == 0)
			qt->double_q++;
		else
			qt->double_q_insimple++;
	}
	if (c == '\'')
	{
		if (qt->double_q % 2 == 0)
			qt->simple_q++;
		else
			qt->simple_q_indouble++;
	}
	return (0);
}
