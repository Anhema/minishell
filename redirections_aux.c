/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:27:53 by aherrero          #+#    #+#             */
/*   Updated: 2022/06/21 17:56:21 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_redirections_aux_continue(int j, int k, int kk, char *str)
{
	char	*value;
	char	*value_aux;
	char	*result;

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
	result = ft_strjoin(value, value_aux);
	free(value_aux);
	free(value);
	return (result);
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
	char	*temp;

	if (j == 0)
	{
		temp = get_redirections_aux_start
			(get_k(str, get_kk(str, j)), get_kk(str, j), str);
	}
	else
		temp = get_redirections_aux_continue
			(j, get_k(str, get_kk(str, j)), get_kk(str, j), str);
	return (temp);
}
