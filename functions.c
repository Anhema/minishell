/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:19:32 by cbustama          #+#    #+#             */
/*   Updated: 2022/04/18 17:32:19 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_sort(char *c)
{
	char	**s;
	char	value;
	int		i;

	i = 0;
	while (c[i])
	{
		if (c[i] == ' ')
			value = ' ';
		else if (c[i] == '\t')
			value = '\t';
		i++;
	}
	s = ft_split(c, value);
	return (s);
}
