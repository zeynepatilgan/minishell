/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksin <taksin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:48:04 by zeatilga          #+#    #+#             */
/*   Updated: 2024/03/10 12:44:41 by taksin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_cmds(t_sdata *data, t_cmd_lst *cmds, char *cmd)
{
	cmd = replace_dollars(cmd, data);
	malloc_and_stock_redir(cmds, cmd);
	cmd = rmv_rdr_from_cmd(cmd);
	cmds->argv = split_arg(cmd);
	if (cmds->argv[0])
		cmds->cmd = ft_strdup_free(cmds->argv[0], 0);
	cmds->cmd_path = NULL;
	cmds->builtin_idx = is_builtin(cmds->cmd);
}

char	*rmv_rdr_from_cmd(char *cmd)
{
	int		count;
	char	*newcmd;

	count = 0;
	newcmd = malloc(sizeof(char *) * (strlen_cmd_without_rdr(cmd) + 1));
	if (!newcmd)
		return (NULL);
	newcmd = find_andsupp_rdr(cmd, newcmd, count);
	free(cmd);
	return (newcmd);
}

char	*find_andsupp_rdr(char *cmd, char *newcmd, int count)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if ((cmd[i] == '<' || cmd[i] == '>') && !duoquote(cmd, i))
		{
			i++;
			if (cmd[i] == '<' || cmd[i] == '>')
				i++;
			i += skip_blank(cmd + i);
			while ((duoquote(cmd, i) || (cmd[i] != ' ' && cmd[i] != '\t'
						&& cmd[i] != '<' && cmd[i] != '>')) && cmd[i])
				i++;
		}
		else
		{
			newcmd[count] = cmd[i];
			count++;
			if (cmd[i])
				i++;
		}
	}
	newcmd[count] = '\0';
	return (newcmd);
}
