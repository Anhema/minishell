/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbustama <cbustama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:56:28 by aherrero          #+#    #+#             */
/*   Updated: 2022/06/07 20:04:21 by cbustama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_stats;

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\33[2K\r");
		printf("\33[2K\r");
		printf("\33[1A");
		printf("^C\n");
		printf("\33[2K\r");
		//g_stats = 130;
	}
	if (signum == SIGQUIT)
	{
		printf ("^\\Quit: 3\n");
		//g_stats = 131;
	}
}

void	continue_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

void	signal_catch(int signum)
{
	if (rl_on_new_line() == -1)
		exit (-1);
	if (SIGINT == signum)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_redisplay();
		g_stats = 1;
	}
}

void	ft_signals(void)
{
	signal(SIGINT, signal_catch);
	//signal(SIGTERM, signal_catch);
	signal(SIGQUIT, SIG_IGN);
}
