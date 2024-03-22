/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeatilga <zeatilga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:46:46 by zeatilga          #+#    #+#             */
/*   Updated: 2024/03/01 19:46:49 by zeatilga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	error_print_free(int rval, char *str, t_sdata *sdata)
{
	if (str)
		putstr_err(str);
	if (sdata)
		deallocate_sdata(sdata);
	return (rval);
}
