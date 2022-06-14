/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbustama <cbustama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:41:22 by aherrero          #+#    #+#             */
/*   Updated: 2022/06/09 20:05:36 by cbustama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**join_env(t_dict *d_env)
{
	char	**env;
	int		i;
	int		j;
	t_dict	*temp;

	temp = d_env;
	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	env = malloc(sizeof(char *) * i);
	temp = d_env;
	j = 0;
	while (temp)
	{
		env[j] = ft_strjoin(temp->key, "=");
		env[j] = ft_strjoin(env[j], temp->value);
		temp = temp->next;
		j++;
	}
	return (env);
}

void	continue_execve(t_data *data, char *key, char **temp)
{
	int	i;

	i = 0;
	key = ft_strreplace(key, "/bin/", "");
	if (key[0] == (char)128
		|| key[0] == (char)129
		|| key[0] == (char)130
		|| key[0] == (char)131)
		return ;
	temp = ft_split(data->commands->value, ' ');
	i = 0;
	if (temp)
	{
		while (temp[i])
			i++;
	}
}
