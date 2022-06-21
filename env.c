/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:49:51 by aherrero          #+#    #+#             */
/*   Updated: 2022/06/21 15:58:16 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dict	*create_env(char **str)
{
	char	**temp;
	int		i;
	t_dict	*env;

	env = NULL;
	i = 0;
	while (str[i])
	{
		temp = ft_split(str[i], '=');
		env = dict_add_back(env, dict_new(temp[0], temp[1]));
		free(temp);
		i++;
	}
	return (env);
}

t_dict	*print_export(char **str, int i, t_data data)
{
	t_dict		*new;
	char		**key_value;
	extern int	g_stats;

	if (!((str[i][0] >= 'a' && str[i][0] <= 'z')
		|| (str[i][0] >= 'A' && str[i][0] <= 'Z')))
	{
		printf("export: `%s': not a valid identifier\n", str[i]);
		return (data.env);
	}
	key_value = ft_split(str[i], '=');
	new = dict_new(key_value[0], key_value[1]);
	data.env = dict_add_back
		(data.env, dict_new(key_value[0], key_value[1]));
	return (data.env);
}

t_dict	*export_aux(char **str, t_data *data, int i)
{
	t_dict	*new;
	char	**key_value;

	if (!((str[i][0] >= 'a' && str[i][0] <= 'z')
	|| (str[i][0] >= 'A' && str[i][0] <= 'Z')
	|| (str[i][0] >= '_')))
	{
		g_stats = 1;
		printf("export: `%s': not a valid identifier\n", str[i]);
		return (data->env);
	}
	key_value = ft_split(str[i], '=');
	new = dict_new(key_value[0], key_value[1]);
	data->env = dict_add_back
		(data->env, dict_new(key_value[0], key_value[1]));
	return (data->env);
}

t_dict	*ft_export(t_data *data)
{
	char	**str;
	t_dict	*temp;
	int		i;

	g_stats = 0;
	if (!data->commands->value)
	{
		temp = data->env;
		while (temp)
		{
			if (temp->value)
				printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
			else
				printf("declare -x %s\n", temp->key);
			temp = temp->next;
		}
		return (data->env);
	}
	str = ft_split(data->commands->value, ' ');
	i = -1;
	while (str[++i])
		data->env = export_aux(str, data, i);
	free_split_double(str);
	return (data->env);
}

t_dict	*ft_unset(t_dict *env, char **str)
{
	int		i;

	i = 0;
	g_stats = 0;
	if (!str)
		return (env);
	while (str[i])
	{
		if (str[i])
			env = del_one(env, str[i]);
		i++;
	}
	return (env);
}
