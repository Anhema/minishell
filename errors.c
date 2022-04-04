/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:33:50 by aherrero          #+#    #+#             */
/*   Updated: 2022/04/04 19:27:55 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	simple(char *str)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			n++;
		i++;
	}
	if (n % 2 == 0)
		return (1);
	return (0);
}

static int	_double(char *str)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			n++;
		i++;
	}
	if (n % 2 == 0)
		return (1);
	return (0);
}

char	*quotation_open(char *str)
{
	char	*temp;
	char	*result;

	result = str;
	if (simple(str) != 1)
	{
		temp = readline("quote> ");
		while (1)
		{
			temp = readline("quote> ");
			if (ft_strchr(temp, '\''))
			{
				result = ft_strjoin(result, temp);
				return (result);
			}
			else
				result = ft_strjoin(result, temp);
		}
	}
	if (_double(str) != 1)
	{
		while (1)
		{
			temp = readline("dquote> ");
			if (ft_strchr(temp, '\"'))
			{
				result = ft_strjoin(result, temp);
				return (result);
			}
			else
				result = ft_strjoin(result, temp);
		}
	}
	return (str);
}
