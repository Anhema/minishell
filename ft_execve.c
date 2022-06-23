/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:41:22 by aherrero          #+#    #+#             */
/*   Updated: 2022/06/22 22:17:00 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**join_env(t_dict *d_env)
{
	char	**env;
	int		i;
	int		j;
	t_dict	*temp;
	char	*tmp;

	temp = d_env;
	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	env = malloc(sizeof(char *) * (i + 1));
	temp = d_env;
	j = 0;
	while (temp)
	{
		tmp = ft_strjoin(temp->key, "=");
		env[j] = tmp;
		env[j] = ft_strjoin(tmp, temp->value);
		temp = temp->next;
		free(tmp);
		j++;
	}
	env[j] = NULL;
	return (env);
}

void	ft_execve(t_data *data)
{
	char	**temp;
	char	**argv;
	char	**env;
	char	*path;
	char	*key;

	argv = NULL;
	path = NULL;
	env = NULL;
	key = ft_strreplace(data->commands->key, "/bin/", "");
	temp = ft_split(data->commands->value, ' ');
	if (!temp)
	{
		argv = malloc(sizeof(char *) * 3);
		argv[0] = key;
		argv[1] = data->commands->value;
		argv[2] = NULL;
	}
	else
		argv = continue_execve(data, temp, argv, key);
	env = join_env(data->env);
	_execve_print(data);
	path = get_path(get_dict_value(data->env, "PATH"), key);
	argv[0] = path;
	if (execve(path, argv, env) < 0)
		print_error(data);
	if (temp)
		free_split_double(temp);
	if (argv)
		free(argv);
	if (env)
		free_split_double(env);
	if (path)
		free(path);
	free(key);
}
