/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeatilga <zeatilga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:46:30 by zeatilga          #+#    #+#             */
/*   Updated: 2024/03/16 16:54:43 by zeatilga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_var_additional_parsing(char *arg, int is_unset)
{
	int	i;
	int	counter;

	counter = 0;
	i = 1;
	while (arg[i])
	{
		if (arg[i] == '=')
			++counter;
		if (arg[i - 1] == '-')
		{
			putstr_err(arg);
			putstr_err(" : not a valid identifier\n");
			return (0);
		}
		if (counter > 0 && is_unset)
			return (0);
		if (counter > 1)
			return (0);
		++i;
	}
	return (1);
}

int	is_env_var_valid(char *arg, int is_unset)
{
	int	i;

	i = 1;
	if (!arg || (len(arg) == 0 && arg[0] == 0))
		return (1);
	if (!is_in_set(arg[0], FIRST_ENV_CHAR_LIST))
		return (1);
	if (!env_var_additional_parsing(arg, is_unset))
		return (1);
	while (is_in_set(arg[i++], ENV_QUOTE))
		return (0);
	i = 1;
	while(arg[i++] && arg[i - 1] == '-' && arg[i + 1] == '\0')
	{
		putstr_err(arg);
		putstr_err(" : not a valid identifier\n");
		return 1;
	}
	return (0);
}

int	does_env_var_exist(t_env_lst *env, char *var)
{
	char	*name;

	name = get_env_var_name_from_arg(var);
	while (env)
	{
		if (!ft_strncmp(env->name, name,
				len(name)) && len(name) == len(env->name))
		{
			free(name);
			return (1);
		}
		env = env->next;
	}
	free(name);
	return (0);
}

int	get_idx_var_in_env(char **env, char *var)
{
	int			i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var,
				lenequal(var) && lenequal(env[i]) == lenequal(var)))
			return (i);
		++i;
	}
	return (-1);
}
