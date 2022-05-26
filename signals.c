/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:56:28 by aherrero          #+#    #+#             */
/*   Updated: 2022/05/26 18:03:59 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\33[2K\r");
		printf("\33[2K\r");
		printf("\33[1A");
		printf("^C\n");
		printf("\33[2K\r");
		exit (0);
	}
	if (signum == SIGQUIT)
	{
		printf ("^\\Quit: 3\n");
		exit (0);
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
		rl_replace_line(" ", 1);
		rl_redisplay();
	}
	if (signum == SIGTERM)
		exit (0);
}

void	ft_signals(void)
{
	signal(SIGINT, signal_catch);
	signal(SIGTERM, signal_catch);
	signal(SIGQUIT, SIG_IGN);
}
