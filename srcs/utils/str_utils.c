/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksin <taksin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:50:31 by zeatilga          #+#    #+#             */
/*   Updated: 2024/03/10 13:05:20 by taksin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	tablen(char **tab)
{
	int				i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		++i;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_number(char const *str, int i)
{
	int		count;

	count = 1;
	if (!(str[i] >= 0 && str[i] <= '9'))
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[++i]))
		++count;
	return (count);
}

int	is_in_set(char c, char const *set)
{
	int		i;

	i = 0;
	if (!set[i])
		return (0);
	while (set[i])
	{
		if (c == set[i])
			return (1);
		++i;
	}
	return (0);
}

int	len(const char *str)
{
	int				i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}
