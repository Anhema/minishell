/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:27:53 by aherrero          #+#    #+#             */
/*   Updated: 2022/06/16 22:59:23 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_redirections_aux_continue(int j, int k, int kk, char *str)
{
	char	*value;
	char	*value_aux;

	value = malloc(sizeof(char) * (j + 1));
	ft_memset(value, 0, sizeof(char) * (j + 1));
	kk = 0;
	while (kk < j)
	{
		value[kk] = str[kk];
		kk++;
	}
	value_aux = malloc
		(sizeof(char) * ((int)ft_strlen(str) - k) + 1);
	ft_memset(value_aux, 0,
		sizeof(char) * ((int)ft_strlen(str) - k) + 1);
	kk = 0;
	while (str[k])
	{
		value_aux[kk] = str[k];
		kk++;
		k++;
	}
	return (ft_strjoin(value, value_aux));
}

char	*get_redirections_aux_start(int k, int kk, char *str)
{
	char	*value;

	value = malloc
		(sizeof(char) * ((int)ft_strlen(str) - k) + 1);
	ft_memset(value, 0,
		sizeof(char) * ((int)ft_strlen(str) - k) + 1);
	kk = 0;
	while (str[k])
	{
		value[kk] = str[k];
		kk++;
		k++;
	}
	return (value);
}

int	get_kk(char *str, int j)
{
	int	kk;

	kk = j + 1;
	while (str[kk] == ' ')
		kk++;
	return (kk);
}

int	get_k(char *str, int kk)
{
	int	k;

	k = kk;
	while (str[k] != '\0' && str[k] != ' '
		&& str[k] != -128 && str[k] != -125
		&& str[k] != -126 && str[k] != -127)
		k++;
	return (k);
}

char	*modify_str(char *str, int j)
{
	if (j == 0)
	{
		str = get_redirections_aux_start
			(get_k(str, get_kk(str, j)), get_kk(str, j), str);
	}
	else
		str = get_redirections_aux_continue
			(j, get_k(str, get_kk(str, j)), get_kk(str, j), str);
	return (str);
}
