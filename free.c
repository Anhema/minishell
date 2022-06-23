/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbustama <cbustama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:17:33 by cbustama          #+#    #+#             */
/*   Updated: 2022/06/23 17:09:51 by cbustama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char *temp)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		free(&temp[i]);
		i++;
	}
	free(temp);
	temp = NULL;
}

void	free_split_double(char **temp)
{
	int	i;

	i = -1;
	if (!temp)
		return ;
	while (temp[++i])
		free(temp[i]);
	free(temp);
	temp = NULL;
}
