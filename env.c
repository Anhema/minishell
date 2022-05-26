/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:49:51 by aherrero          #+#    #+#             */
/*   Updated: 2022/05/26 17:58:46 by aherrero         ###   ########.fr       */
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

void	print_dict(t_dict *env)
{
	t_dict	*temp;

	temp = env;
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
				env = temp;
			}
			else
			{
				temp = env->next;
				env = temp;
			}
		}
	}
}

t_dict	*print_export(char **str, int i, t_data data)
{
	t_dict	*new;
	char	**key_value;

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

t_dict	*ft_export(t_data data)
{
	char	**str;
	t_dict	*temp;
	int		i;
	t_dict	*new;
	char	**key_value;

	if (!data.commands->value)
	{
		temp = data.env;
		while (temp)
		{
			if (temp->value)
				printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
			else
				printf("declare -x %s\n", temp->key);
			temp = temp->next;
		}
		return (data.env);
	}
	str = ft_split(data.commands->value, ' ');
	i = 0;
	while (str[i])
	{
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
		i++;
	}
	return (data.env);
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
