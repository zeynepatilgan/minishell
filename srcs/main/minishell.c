/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksin <taksin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:47:23 by zeatilga          #+#    #+#             */
/*   Updated: 2024/03/10 15:26:44 by taksin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	while_for_shell_loop(t_sdata *sdata, char *line)
{
	while (1)
	{
		g_signal = 0;
		line = readline("\033[33mZeynep&Tuba$➜\033[00m ");
		g_signal = 1;
		if (line == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (line[0] == 0 || empty_str(line) || check_line(line) == -1)
		{
			free(line);
			continue ;
		}
		add_history(line);
		sdata->nb_of_cmds = check_line(line);
		sdata->f_cmds = parse_line(sdata, line);
		sdata->cmds = sdata->f_cmds;
		if (!sdata->cmds->cmd)
			continue ;
		send_to_exec(sdata);
		free(line);
	}
}

int	main(int ac, char **argv, char **env)
{
	t_sdata		sdata;

	(void)argv;
	if (ac != 1)
	{
		write(1, "Minishell can't have more than 0 argument\n", 43);
		return (0);
	}
	allocate_sdata(&sdata, env);
	assign_signals_handler();
	shell_loop(&sdata);
	deallocate_sdata(&sdata);
}
