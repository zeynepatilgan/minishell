/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_executable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksin <taksin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:47:58 by zeatilga          #+#    #+#             */
/*   Updated: 2024/03/10 13:39:06 by taksin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_paths_from_env(t_env_lst *env)
{
	char	*path;

	path = get_env_var_from_name(env, "PATH");
	if (!path)
		return (NULL);
	return (str_to_word_arr(path, ':'));
}

char	*is_cmd_in_path(char *cmd, char **paths)
{
	char	*path;
	int		i;
	int		fd;

	i = 0;
	while (paths[i])
	{
		if (cmd[0] != '/')
			path = cncat(cncat(paths[i], "/", 0, 0), cmd, 1, 0);
		else
			path = ft_strdup_free(cmd, 0);
		fd = open(path, O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			return (path);
		}
		free(path);
		++i;
	}
	return (NULL);
}

char	*does_binary_file_exists(char *cmd)
{
	int	fd;

	if (!ft_strncmp(cmd, "./", 2))
		fd = open(cmd + 2, O_RDONLY);
	else
		fd = open(cmd, O_RDONLY);
	if (fd == -1)
		return (NULL);
	else
	{
		close(fd);
		return (cmd);
	}
}

char	*is_cmd_executable(char *cmd, t_sdata *sdata)
{
	char	**paths;
	char	*abs_cmd;

	if (!ft_strncmp(cmd, "/", 1) || !ft_strncmp(cmd, "./", 2))
		return (ft_strdup_free(does_binary_file_exists(cmd), 0));
	paths = get_paths_from_env(sdata->env_lst);
	if (!paths)
		return (NULL);
	abs_cmd = is_cmd_in_path(cmd, paths);
	free_arr(paths);
	return (abs_cmd);
}

int	is_builtin(char *cmd)
{
	int			i;
	const char	*g_builtins_mask[ARR_SIZE] = {"env", "export",
		"unset", "pwd", "echo", "cd", "exit"};

	if (!cmd)
		return (-1);
	i = 0;
	while (i < 7)
	{
		if (!ft_strncmp(g_builtins_mask[i], cmd, len(g_builtins_mask[i]))
			&& len(cmd) == len(g_builtins_mask[i]))
			return (i);
		++i;
	}
	if (i == 7)
		return (-1);
	return (i);
}
