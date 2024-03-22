/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksin <taksin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:49:38 by zeatilga          #+#    #+#             */
/*   Updated: 2024/03/02 12:51:06 by taksin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*ft_bzero(size_t n)
{
	void	*ptr;
	int		i;

	ptr = malloc(n);
	if (!ptr)
		return (NULL);
	i = 0;
	if (!ptr)
		return (NULL);
	while ((size_t)i < n)
	{
		((char *)ptr)[i] = 0;
		++i;
	}
	return (ptr);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t		i;

	i = 0;
	if (!n)
		return (0);
	while (s1[i] && s2[i] && i < n - 1)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - s2[i]);
		++i;
	}
	return ((unsigned char)s1[i] - s2[i]);
}

int	nbr_of_word(char *av, char sep)
{
	int				i;
	int				count;

	count = 1;
	i = 0;
	if (!av || !av[i])
		return (0);
	while (av[i])
	{
		if (av[i] != sep)
		{
			while (av[i] && av[i] != sep)
				++i;
			++count;
			continue ;
		}
		++i;
	}
	return (count);
}

int	find_quotes(char *cmd, int i, char c)
{
	if (!(cmd[i] == '\'' || cmd[i] == '\"'))
		return (i);
	i++;
	while (cmd[i] != c)
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (unsigned char) c)
			return ((char *)s);
		s++;
	}
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}
