/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeatilga <zeatilga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:50:09 by zeatilga          #+#    #+#             */
/*   Updated: 2024/03/01 19:50:11 by zeatilga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**new_arr(char *str)
{
	char	**arr;

	arr = malloc(sizeof(char *) * 2);
	if (!arr)
		return (NULL);
	arr[0] = ft_strdup_free(str, 1);
	arr[1] = NULL;
	return (arr);
}

char	**extend_arr(char **arr, char *str)
{
	int			i;
	char		**n_arr;

	i = 0;
	n_arr = malloc(sizeof(char *) * (tablen(arr) + 2));
	if (!n_arr)
		return (NULL);
	while (arr[i])
	{
		n_arr[i] = arr[i];
		++i;
	}
	n_arr[i] = ft_strdup_free(str, 0);
	n_arr[i + 1] = NULL;
	free(arr);
	return (n_arr);
}

char	**cncat_arr(char **arr, char *str)
{
	if (!arr)
		return (new_arr(str));
	else
		return (extend_arr(arr, str));
}

char	**dup_arr(char **arr)
{
	char	**n_arr;
	int		len;
	int		i;

	i = 0;
	if (!arr)
		return (NULL);
	len = tablen(arr);
	n_arr = malloc(sizeof(char *) * (1 + len));
	if (!n_arr)
		return (NULL);
	while (i < len)
	{
		n_arr[i] = ft_strdup_free(arr[i], 0);
		++i;
	}
	n_arr[i] = NULL;
	return (n_arr);
}
