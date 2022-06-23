/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbustama <cbustama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 19:11:20 by aherrero          #+#    #+#             */
/*   Updated: 2022/06/23 18:09:34 by cbustama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_dict_value(t_dict *dict, char	*key)
{
	t_dict	*temp;

	temp = dict;
	if (!dict)
		return (NULL);
	else
	{
		while (dict != NULL)
		{
			if (ft_str_equals(temp->key, key) == 1)
				return (temp->value);
			temp = dict->next;
			dict = temp;
		}
	}
	return (NULL);
}

void	delete_all(t_dict *dict)
{
	t_dict	*temp;

	if (!dict)
		return ;
	while (dict)
	{
		temp = dict->next;
		if (dict->key)
			free (dict->key);
		if (dict->value)
			free (dict->value);
		free(dict);
		dict = temp;
	}
	free(dict);
	dict = NULL;
}

void	print_dict(t_dict *env)
{
	t_dict	*temp;

	temp = env;
	g_stats = 0;
	if (!env)
	{
		printf("DICT NULL\n");
		return ;
	}
	else
	{
		while (env)
		{
			if (temp->value)
			{
				printf("%s=%s\n", temp->key, temp->value);
				temp = env->next;
			}
			else
				temp = env->next;
			env = temp;
		}
	}
}
