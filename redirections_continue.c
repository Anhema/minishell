/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_continue.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:51:51 by aherrero          #+#    #+#             */
/*   Updated: 2022/06/16 21:24:44 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	aux_aux(int n, char *c, char *str, int j)
{
	if (n == 0)
	{
		if (str[j] == '\"')
		{
			*c = '\"';
			n++;
		}
		if (str[j] == '\'')
		{
			*c = '\'';
			n++;
		}
	}
	else if (c && str[j] == *c)
	{
		if (n > 0)
		{
			*c = 0;
			n--;
		}
		else
			n++;
	}
	return (n);
}
