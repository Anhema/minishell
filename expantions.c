/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbustama <cbustama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:55:58 by cbustama          #+#    #+#             */
/*   Updated: 2022/06/07 19:53:48 by cbustama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_stats;

void	expand_execve(t_data *data, int status)
{
	(void)data;
	printf("execve\n");
	printf("despues del waitpid %d\n", g_stats);
	if (WIFEXITED(status))
		g_stats = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			g_stats = 130;
		else if ((WTERMSIG(status) == 3))
			g_stats = 131;
		printf("señales %d\n", g_stats);
	}
}

/*void	expantions(int status, t_data *data)
{
	
	if (data->bool == 0)
	{
		printf("data->status %d \n", data->status);
	printf("data->bool %d\n", data->bool);
		if (WIFEXITED(status))
			data->status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == 2)
				data->status = 1;
			else if ((WTERMSIG(status) == 3))
				data->status = 0;
		}
		printf("builtins %d\n", data->status);
	}
}*/

void	print_expantions(void)
{
	g_stats = 127;
	printf("%d: command not found\n", g_stats);
	
}

