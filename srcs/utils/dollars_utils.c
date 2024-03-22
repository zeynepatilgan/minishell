/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeatilga <zeatilga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:49:15 by zeatilga          #+#    #+#             */
/*   Updated: 2024/03/01 19:49:17 by zeatilga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_in_set(str[i], ENV_CHAR_LIST))
			return (i);
		i++;
	}
	return (i);
}

int	int_len(int i)
{
	int	count;

	count = 1;
	while (i > 9)
	{
		i = i / 10;
		count++;
	}
	return (count);
}
