/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_sdata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeatilga <zeatilga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:47:33 by zeatilga          #+#    #+#             */
/*   Updated: 2024/03/17 15:27:01 by zeatilga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd_lst	*allocate_cmd_elem(void)
{
	t_cmd_lst	*cmd;

	cmd = malloc(sizeof(t_cmd_lst));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->argv = NULL;
	cmd->cmd_path = NULL;
	cmd->fd_stack = NULL;
	cmd->fd_nbr = 0;
	return (cmd);
}

t_env_lst	*allocate_env_lst_elem(char **line)
{
	t_env_lst	*elem;

	if (!line)
		return (NULL);
	elem = malloc(sizeof(t_env_lst));
	if (!elem)
		return (NULL);
	elem->name = line[0];
	elem->var = line[1];
	elem->next = NULL;
	free(line);
	return (elem);
}

int	allocate_env_lst(t_sdata *sdata, char **env)
{
	t_env_lst	*elem;
	t_env_lst	*next;
	int			i;

	i = 0;
	if (!env || !env[0])
		return (EXIT_FAILURE);
	sdata->env_lst = allocate_env_lst_elem(split_env(env[0], '='));
	if (!sdata->env_lst)
		return (1);
	elem = sdata->env_lst;
	while (env[++i])
	{
		next = allocate_env_lst_elem(split_env(env[i], '='));
		if (!next)
			return (deallocate_env_lst(sdata->env_lst));
		elem->next = next;
		elem = next;
	}
	elem->next = NULL;
	return (EXIT_SUCCESS);
}

void	allocate_sdata(t_sdata *sdata, char **env)
{
	sdata->cmds = NULL;
	sdata->f_cmds = NULL;
	sdata->lrval = 0;
	sdata->env = dup_arr(env);
	if (allocate_env_lst(sdata, sdata->env) == EXIT_FAILURE)
		sdata->env_lst = NULL;
	sdata->lrval = 0;
	sdata->save_stdin = dup(0);
	sdata->save_stdout = dup(1);
	if (!sdata->env_lst)
		sdata->bin_paths = NULL;
	else
		sdata->bin_paths = str_to_word_arr(
				get_var_in_env(env, "PATH=") + 5, ':');
}
