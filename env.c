/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbustama <cbustama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:49:51 by aherrero          #+#    #+#             */
/*   Updated: 2022/04/20 17:01:23 by cbustama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dict	*create_env(char **str)
{
	char	**temp;
	int		i;
	t_dict	*env;
	t_dict	*new;

	env = NULL;
	i = 0;
	while (str[i])
	{
		temp = ft_split(str[i], '=');
		new = dict_new(temp[0], temp[1]);
		env = dict_add_back(env, new);
		i++;
	}
	return (env);
}

void	print_env(t_dict *env)
{
	t_dict	*temp;

	temp = env;
	if (!env)
	{
		printf("ENV NULL\n");
		return ;
	}
	else
	{
		while (env != NULL)
		{
			if (temp->value)
			{
				printf("%s=%s\n", temp->key, temp->value);
				temp = env->next;
				env = temp;
			}
		}
	}
}

t_dict	*ft_export(t_dict *env, char **str)
{
	char	**key_value;
	t_dict	*new;
	t_dict	*temp;
	int		i;

	if (!str[1])
	{
		temp = env;
		while (temp != NULL)
		{
			if (temp->value)
			{
				printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
				temp = temp->next;
			}
		}
		return (env);
	}
	i = 1;
	while (str[i])
	{
		key_value = ft_split(str[i], '=');
		new = dict_new(key_value[0], key_value[1]);
		env = dict_add_back(env, dict_new(key_value[0], key_value[1]));
		i++;
	}
	return (env);
}

t_dict	*ft_unset(t_dict *env, char **str)
{
	int		i;

	i = 1;
	while (str[i])
	{
		env = del_one(env, str[i]);
		i++;
	}
	return (env);
}
