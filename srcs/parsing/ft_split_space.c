/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksin <taksin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:48:16 by zeatilga          #+#    #+#             */
/*   Updated: 2024/03/10 12:45:26 by taksin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_words_space(const char *str, char c)
{
	int	i;
	int	trigger;
	int	s_quotes;
	int	d_quotes;

	s_quotes = 0;
	d_quotes = 0;
	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str == '\'')
			s_quotes++;
		if (*str == '\"')
			d_quotes++;
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c && (s_quotes % 2 == 0 && d_quotes % 2 == 0))
			trigger = 0;
		str++;
	}
	return (i);
}

char	**split_the_pipe(char const *s)
{
	size_t	i;
	int		j;
	char	**split;

	j = 0;
	if (!s)
		return (0);
	split = malloc((count_words_space(s, '|') + 1) * sizeof(char *));
	if (!split)
		return (0);
	i = 0;
	return (skip_quotes_split(s, i, split, j));
}

int	nb_of_args(char *cmd)
{
	int	i;
	int	size;
	int	j;

	size = 0;
	i = skip_blank(cmd);
	if (cmd[i])
		size++;
	while (cmd[i])
	{
		j = i;
		i = skip_quotes_arg(cmd, i);
		if ((cmd[i] == ' ' || cmd[i] == '\t'
				|| cmd[i] == '<' || cmd[i] == '>') && i == j)
		{
			size++;
			i += skip_blank(cmd + i);
			if (!cmd[i])
				size--;
		}
		else if (i == j)
			i++;
	}
	return (size);
}

char	**split_arg(char *s)
{
	char		**split;
	t_split_arg	sp;

	sp.j = 0;
	sp.i = 0;
	sp.size = 0;
	sp.size = nb_of_args(s);
	split = malloc(sizeof(char *) * (sp.size + 1));
	if (!split)
		return (NULL);
	sp.v = 0;
	while (sp.i < sp.size)
	{
		sp.v = find_lenght_file(s + sp.j);
		split[sp.i] = malloc(sizeof(char *) * (sp.v + 1));
		if (!split)
			return (NULL);
		split[sp.i] = get_file_redir(s + sp.j, split[sp.i]);
		sp.j += find_lenghtwq(s + sp.j);
		sp.i++;
	}
	split[sp.i] = NULL;
	free(s);
	return (split);
}

char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}
