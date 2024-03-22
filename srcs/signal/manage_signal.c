/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksin <taksin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:49:05 by zeatilga          #+#    #+#             */
/*   Updated: 2024/03/10 14:08:22 by taksin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handler(int signum)
{
	if (g_signal == 10)
	{
		if (signum == CTRL_C)
		{
			printf("\n");
			exit(1);
		}
	}
	else if (!g_signal && signum == CTRL_C)
	{
		printf("\n");
		//rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == CTRL_SLASH)
	{
		if (g_signal == 10)
			g_signal = 0;
		else
			g_signal = 10;
		printf("Quit: 3\n");
	}
}

void	assign_signals_handler(void)
{
	signal(CTRL_C, handler);
	signal(CTRL_SLASH, handler);
}
