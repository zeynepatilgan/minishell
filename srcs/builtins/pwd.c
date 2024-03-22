/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeatilga <zeatilga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:46:17 by zeatilga          #+#    #+#             */
/*   Updated: 2024/03/01 19:46:20 by zeatilga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(t_sdata *sdata)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		sdata->lrval = 1;
		return ;
	}
	write(1, path, len(path));
	write(1, "\n", 1);
	free(path);
	sdata->lrval = 0;
}
