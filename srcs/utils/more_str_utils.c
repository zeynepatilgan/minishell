/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_str_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksin <taksin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:49:53 by zeatilga          #+#    #+#             */
/*   Updated: 2024/03/10 13:06:18 by taksin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	empty_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		++i;
	}
	return (1);
}

int	skip_blank(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
		i++;
	return (i);
}

int	is_maj(char c)
{
	if ((c > 64) && (c < 91))
		return (1);
	if ((c > 96) && (c < 123))
		return (1);
	return (0);
}

void	putstr_err(char *str)
{
	if (!str)
		return ;
	write(2, str, len(str));
}

char	*put_int_str(int nb_len, char *cmd, int count, int lrval)
{
	if (nb_len == 3)
	{
		cmd[count] = (lrval / 100) + 48;
		cmd[count + 1] = ((lrval / 10) % 10) + 48;
		cmd[count + 2] = (lrval % 10) + 48;
	}
	if (nb_len == 2)
	{
		cmd[count] = (lrval / 10) + 48;
		cmd[count + 1] = (lrval % 10) + 48;
	}
	if (nb_len == 1)
		cmd[count] = lrval + 48;
	return (cmd);
}
