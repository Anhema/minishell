/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:49:51 by aherrero          #+#    #+#             */
/*   Updated: 2022/04/12 17:46:38 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dict	*create_env(char **str)
{
	char	**temp;
	int		i;
	t_dict	*env;
	t_dict	*new;

	i = 0;
	while (str[i])
	{
		temp = ft_split(str[i], '=');
		new = dict_new(temp[0], temp[1]);
		env = dict_add_back(env, dict_new(temp[0], temp[1]));
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
			printf("%s=%s\n", temp->key, temp->value);
			temp = env->next;
			env = temp;
		}
	}
}
